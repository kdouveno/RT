/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_antialiasing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:33:50 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/14 12:34:58 by schaaban         ###   ########.fr       */
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
		ls[1].m = apply(vecpro(apply(d->x, rev_3d(d->y)), c), l.m);
		ls[2].m = apply(vecpro(apply(rev_3d(d->x), d->y), c), l.m);
		ls[3].m = apply(rev_3d(vecpro(apply(d->x, d->y), c)), l.m);
	}
	else
	{
		c = 1 / (m * 4.0);
		ls[0].v = apply(vecpro(apply(d->x, d->y), c), l.v);
		ls[1].v = apply(vecpro(apply(d->x, rev_3d(d->y)), c), l.v);
		ls[2].v = apply(vecpro(apply(rev_3d(d->x), d->y), c), l.v);
		ls[3].v = apply(rev_3d(vecpro(apply(d->x, d->y), c)), l.v);
	}
}

t_color					rec_raytrace(t_rendering *r, t_line l, int m)
{
	t_cam_render	*d;
	t_line			ls[4];

	if (m <= 1)
		pthread_mutex_unlock(&r->lock);
	d = &r->c->data;
	if (m < d->ssaa && m)
	{
		assign_lines(ls, l, m, d);
		return (rgbmoy4((t_color[]){rec_raytrace(r, ls[0], m * 2),
			rec_raytrace(r, ls[1], m * 2), rec_raytrace(r, ls[2], m * 2),
			rec_raytrace(r, ls[3], m * 2)}));
	}
	else
		return (raytrace(r, l, 0, (t_ri){NULL, NULL, NULL, 1, 'c'}));
}

inline static int		aaacolor(t_color a, t_color b)
{
	if (abs(a.p.r - b.p.r) > AAA_THRESH)
		return (1);
	if (abs(a.p.g - b.p.g) > AAA_THRESH)
		return (1);
	if (abs(a.p.b - b.p.b) > AAA_THRESH)
		return (1);
	return (0);
}

inline static t_line	get_camline(t_cam c, int i)
{
	t_line			out;
	double			step;
	t_cam_render	*d;

	d = &c.data;
	out = (t_line){d->pt_ul, {}};
	i++;
	if (d->para)
	{
		step = d->fov / d->dimx;
		out.m = apply(trans_vec((t_vec){0, d->fov / 2 - step
			* (i % d->dimx + 1), d->dimy * step / 2 - step
			* (i / d->dimx + 1)}, &c.m), d->pt_ul);
		out.v = d->vp_ul;
	}
	else
	{
		out.v = trans_vec((t_vec){(double)(d->dimx / 2) / tan(rad(d->fov) / 2),
		d->dimx / 2 - i % d->dimx + 1,
		d->dimy / 2 - i / d->dimx + 1}, &c.m);
	}
	return (out);
}

void					aaa(t_rendering *r)
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
		((t_rendering*)r)->e->ui.pbar.value = ((double)i
			/ (double)max);
		i++;
	}
}
