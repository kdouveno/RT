/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 14:13:40 by gperez            #+#    #+#             */
/*   Updated: 2018/11/12 17:01:46 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void init_objs(t_env *e) {
	t_obj	*objs;

	objs = e->s.objs;
	while (objs)
	{
		if (objs->r >= 0)
			objs->dir = get_rot(objs->dir, objs->r);
		else
			objs->dir = (t_three_d){rad(objs->dir.x),
			rad(objs->dir.y), rad(objs->dir.z)};
		if (objs->type == CONE)
			objs->v[0] = rad(objs->v[0]);
		objs = objs->next;
	}
}

void	init_cam(t_env *e)
{
	t_cam			*cams;
	t_cam_render	*d;

	cams = e->s.cams;
	while (cams != NULL)
	{
		d = &cams->data;
		if (cams->r >= 0)
			cams->dir = get_rot(cams->dir, cams->r);
		else
			cams->dir = (t_three_d){rad(cams->dir.x),
			rad(cams->dir.y), rad(cams->dir.z)};
		d->dimx = DIMX;
		d->dimy = DIMY;
		d->xmax = d->dimx * d->antialia;
		d->ymax = d->dimy * d->antialia;
		d->vp_ul = rot((t_vec){(double)(-d->xmax / 2) / tan(d->fov / 2),
			-d->xmax / 2, d->ymax / 2}, cams->dir);
		d->x = rot((t_vec){0, 1, 0}, cams->dir);
		d->y = rot((t_vec){0, -d->xmax + 1, -1}, cams->dir);
		if (!(d->render = SDL_CreateRGBSurface(0, d->xmax, d->ymax,
		32, RMASK, GMASK, BMASK, AMASK)))
			error(e, SDL_GetError());
		cams = cams->next;
	}
}

t_color		init_lit_scene(t_scene *s)
{
	t_lit	*l;

	l = s->lits;
	while (l)
	{
		s->amb_lit_c = rgbadd(s->amb_lit_c, l->color);
		l = l->next;
	}
	return (s->amb_lit_c);
}

void	init(t_env *e)
{
	t_prst	*p;

	p = e->p;
	init_cam(e);
	init_objs(e);
	init_lit_scene(&(e->s));
	while (p)
	{
		e->s.amb_lit_c = rgbadd(init_lit_scene(&(e->p->s)), e->s.amb_lit_c);
		p = p->next;
	}
}
