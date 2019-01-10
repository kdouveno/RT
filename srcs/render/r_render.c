/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:19:08 by gperez            #+#    #+#             */
/*   Updated: 2019/01/10 14:16:58 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
