/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:19:08 by gperez            #+#    #+#             */
/*   Updated: 2018/11/27 18:06:18 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	rec_raytrace(t_rendering *r, t_line l, int m)
{
	t_cam_render	*d;
	t_vec			v[4];

	if (m == 1)
		pthread_mutex_unlock(&r->lock);
	d = &r->c->data;
	if (m < d->antialia)
	{
		v[0] = apply(vecpro(apply(d->x, d->y), 1 / (m * 4.0)), l.v);
		v[1] = apply(vecpro(apply(d->x, vec_rev(d->y)), 1 / (m * 4.0)), l.v);
		v[2] = apply(vecpro(apply(vec_rev(d->x), d->y), 1 / (m * 4.0)), l.v);
		v[3] = apply(vec_rev(vecpro(apply(d->x, d->y), 1 / (m * 4.0))), l.v);
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

void	*render(void *r)
{
	int				ix;
	int				iy;
	t_line			l;
	t_cam_render	*d;

	iy = 0;
	d = &((t_rendering*)r)->c->data;
	while (d->iy < d->dimy)
	{
		// pthread_mutex_lock(&((t_rendering*)r)->lock);
		ix = d->ix++;
		iy = d->iy;
		l = (t_line){((t_rendering*)r)->c->t, d->vp_ul};
		if (d->ix >= d->dimx)
		{
			d->ix = 0;
			d->iy++;
			d->vp_ul = apply(d->xy, d->vp_ul);
		}
		else
			d->vp_ul = apply(d->x, d->vp_ul);
		// if (ix == DIMX / 2 && iy == DIMY / 2)
		((int*)d->render->pixels)[iy * d->dimx + ix] = rec_raytrace(r, l, 1).i;
	}
	pthread_exit(NULL);
	return (NULL);
}

t_cam	*render_cam(t_env *e, int ncam)
{
	t_rendering		r;
	pthread_t		thds[THRD_CNT];
	int				i;
	t_cam			*c;

	r.lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	r.e = e;
	i = 0;
	c = e->s.cams;
	while (i++ < ncam && c)
		c = c->next;
	if (!c)
		return (NULL);
	r.c = c;
	i = 0;
	while (i < THRD_CNT)
	{
		if (pthread_create(thds + i, NULL, &render, &r))
			error(e, PTHR_ERROR);
		i++;
	}
	while (i >= 0)
		pthread_join(thds[i--], NULL);

	return (c);
}
