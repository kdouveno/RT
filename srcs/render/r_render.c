/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:19:08 by gperez            #+#    #+#             */
/*   Updated: 2018/12/20 13:37:03 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		assign_lines(t_line ls[4], t_line l, int m, t_cam_render *d)
{
	double c;

	ls[0] = l;
	ls[1] = l;
	ls[2] = l;
	ls[3] = l;
	if (d->para)
	{
		c = d->fov / (d->dimx * m * 4.0);
		ls[0].m = apply(vecpro(apply(d->x, d->y), c), l.m);
		ls[1].m = apply(vecpro(apply(d->x, vec_rev(d->y)), c), l.m);
		ls[2].m = apply(vecpro(apply(vec_rev(d->x), d->y), c), l.m);
		ls[3].m = apply(vec_rev(vecpro(apply(d->x, d->y), c)), l.m);
	}
	else
	{
		c = 1 / (m * 4.0);
		ls[0].v = apply(vecpro(apply(d->x, d->y), c), l.v);
		ls[1].v = apply(vecpro(apply(d->x, vec_rev(d->y)), c), l.v);
		ls[2].v = apply(vecpro(apply(vec_rev(d->x), d->y), c), l.v);
		ls[3].v = apply(vec_rev(vecpro(apply(d->x, d->y), c)), l.v);
	}
}

t_color	rec_raytrace(t_rendering *r, t_line l, int m)
{
	t_cam_render	*d;
	t_line			ls[4];

	if (m <= 1)
		pthread_mutex_unlock(&r->lock);
	d = &r->c->data;
	if (m < d->ssaa && m)
	{
		assign_lines(ls, l, m, d);
		return (rgbmoy4((t_color[]){
			rec_raytrace(r, ls[0], m * 2),
			rec_raytrace(r, ls[1], m * 2),
			rec_raytrace(r, ls[2], m * 2),
			rec_raytrace(r, ls[3], m * 2),
		}));
	}
	else
		return (raytrace(r, l, 0));
}

static void	render_next_line(t_cam_render *d)
{
	if (d->ix >= d->dimx)
	{
		d->ix = 0;
		d->iy++;
		if (d->para)
			d->pt_ul = apply(d->xy, d->pt_ul);
		else
			d->vp_ul = apply(d->xy, d->vp_ul);
	}
	else if (d->para)
		d->pt_ul = apply(d->x, d->pt_ul);
	else
		d->vp_ul = apply(d->x, d->vp_ul);
}

void	*render(void *r)
{
	int				ix;
	int				iy;
	t_line			l;
	t_cam_render	*d;

	d = &((t_rendering*)r)->c->data;
	while (1)
	{
		pthread_mutex_lock(&((t_rendering*)r)->lock);
		if (d->iy >= d->dimy)
			break ;
		ix = d->ix++;
		iy = d->iy;
		l = (t_line){d->pt_ul, d->vp_ul};
		render_next_line(d);
		((int*)d->render->pixels)[iy * d->dimx + ix] = rec_raytrace(
			r, l, !d->aaa).i;
		((t_rendering*)r)->e->ui.pbar.value = (((double)iy
			/ (double)d->dimy)) * (1.0 - ((double)d->ssaa / 32.0));
	}
	pthread_mutex_unlock(&((t_rendering*)r)->lock);
	pthread_exit(NULL);
	return (NULL);
}

int		aaacolor(t_color a, t_color b)
{
	if (abs(a.p.r - b.p.r) > AAA_THRESH)
		return (1);
	if (abs(a.p.g - b.p.g) > AAA_THRESH)
		return (1);
	if (abs(a.p.b - b.p.b) > AAA_THRESH)
		return (1);
	// printf("0\n");

	return (0);
}

t_line	get_camline(t_cam c, int i)
{
	t_line			out;
	double			step;
	t_cam_render	*d;

	d = &c.data;
	out = (t_line){c.t, {}};
	i++;
	if (c.data.para)
	{
		step = d->fov / d->dimx;
		out.m = apply(rot((t_vec){0, d->fov / 2 - step * (i % d->dimx + 1),
			d->dimy * step / 2 - step * (i / c.data.dimx + 1)},
			c.dir), c.t);
		out.v= d->vp_ul;
	}
	else
	{
		out.v = rot((t_vec){(double)(c.data.dimx / 2) / tan(rad(c.data.fov) / 2),
		c.data.dimx / 2 - i % c.data.dimx + 1,
		c.data.dimy / 2 - i / c.data.dimx + 1}, c.dir);
	}
	return (out);
}

void	aaa(t_rendering *r)
{
	long			i;
	long			max;
	t_cam_render	*d;
	t_color			*p;

	d = &r->c->data;
	if (!d->aaa)
		return ;
	max = d->dimx * d->dimy;
	p = (t_color*)d->render->pixels;
	i = 0;
	while (i < max)
	{
		if ((i > d->dimx && aaacolor(p[i], p[i - d->dimx]))
		|| ((i + 1) % d->dimx != 1 && aaacolor(p[i], p[i - 1]))
		|| ((i + 1) % d->dimx && aaacolor(p[i], p[i + 1]))
		|| (i < max - d->dimx && aaacolor(p[i], p[i + d->dimx])))
			p[i] = rec_raytrace(r, get_camline(*r->c, i), 1);
		((t_rendering*)r)->e->ui.pbar.value = (((double)i
			/ (double)max) * ((double)d->ssaa / 32.0))
			+ (1.0 - ((double)d->ssaa / 32.0));
		i++;
	}
}

t_cam	*render_cam(t_env *e, int ncam)
{
	t_rendering		r;
	pthread_t		thds[e->glb.thread_count];
	int				i;
	t_cam			*c;

	i = 0;
	c = e->s.cams;
	while (i++ < ncam && c)
		c = c->next;
	if (!c)
		return (NULL);
	r = (t_rendering){PTHREAD_MUTEX_INITIALIZER, e, c};
	if (r.c->data.iy >= r.c->data.dimy)
		return (c);
	i = 0;
	while (i < e->glb.thread_count)
	{
		if (pthread_create(thds + i, NULL, &render, &r))
			error(e, PTHR_ERROR);
		i++;
	}
	i = 0;
	while (i < e->glb.thread_count)
		pthread_join(thds[i++], NULL);
	c->data.ssaa > 1 ? aaa(&r) : 0;
	return (c);
}
