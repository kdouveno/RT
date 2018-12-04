/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:19:08 by gperez            #+#    #+#             */
/*   Updated: 2018/12/04 16:35:06 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	rec_raytrace(t_rendering *r, t_line l, int m, t_cam c)
{
	t_cam_render	*d;
	t_line			v[4];
	t_three_d		*t;
	double			c;

	if (m <= 1)
		pthread_mutex_unlock(&r->lock);
	t = c.data.para ? &l.m - &l : &l.v - &l;
	c = (c.data.para ? c.data.fov / c.data.dimx : 1) / (m * 4.0);
	d = &r->c->data;
	if (m < d->ssaa && m)
	{
		v[0] = apply(vecpro(apply(d->x, d->y), c), l.v);
		v[1] = apply(vecpro(apply(d->x, vec_rev(d->y)), c), l.v);
		v[2] = apply(vecpro(apply(vec_rev(d->x), d->y), c), l.v);
		v[3] = apply(vec_rev(vecpro(apply(d->x, d->y), c)), l.v);
		return (rgbmoy4((t_color[]){
			rec_raytrace(r, (t_line){l.m, v[0]}, m * 2),
			rec_raytrace(r, (t_line){l.m, v[1]}, m * 2),
			rec_raytrace(r, (t_line){l.m, v[2]}, m * 2),
			rec_raytrace(r, (t_line){l.m, v[3]}, m * 2),
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
	int				tmp;

	d = &r->c->data;
	if (!d->aaa)
		return ;
	max = d->dimx * d->dimy;
	p = (t_color*)d->render->pixels;
	i = 0;
	while (i < max)
	{
		tmp = 0;
		// if (p[i].i != 0xff000000)
		// printf("\n%x\n%x %x %x\n%x\n", p[i - d->dimx].i, p[i - 1].i, p[i].i,
			// p[i + 1].i, p[i + d->dimx].i);
		if ((i > d->dimx && aaacolor(p[i], p[i - d->dimx]))
		|| ((i + 1) % d->dimx != 1 && aaacolor(p[i], p[i - 1]))
		|| ((i + 1) % d->dimx && aaacolor(p[i], p[i + 1]))
		|| (i < max - d->dimx && aaacolor(p[i], p[i + d->dimx])))
			p[i] = rec_raytrace(r, get_camline(*r->c, i), 1);
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
