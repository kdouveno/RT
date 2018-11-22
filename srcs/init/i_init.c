/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 14:13:40 by gperez            #+#    #+#             */
/*   Updated: 2018/11/22 10:42:34 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_grads(t_scene *s)
{
	t_obj	*objs;
	t_grad	*grads;

	grads = s->grads;
	while (grads)
	{
		grads->dir = get_vector(grads->t, grads->dir);
		grads->r = get_rot(grads->dir, 0);
		grads = grads->next;
	}
	objs = s->objs;
	while (objs)
	{
		grads = s->grads;
		while (grads)
			if (grads->id == objs->id)
			{
				objs->grad = grads;
				grads = NULL;
			}
			else
				grads = grads->next;
		objs = objs->next;
	}
}

void		init_cam(t_env *e, t_scene *s)
{
	t_cam			*cams;
	t_cam_render	*d;

	cams = s->cams;
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
		d->vp_ul = rot((t_vec){(double)(-d->dimx / 2) / tan(d->fov / 2),
			-d->dimx / 2, d->dimy / 2}, cams->dir);
		d->x = rot((t_vec){0, 1, 0}, cams->dir);
		d->y = rot((t_vec){0, 0, -1}, cams->dir);
		d->xy = rot((t_vec){0, -d->dimx + 1, -1}, cams->dir);
		if (!(d->render = SDL_CreateRGBSurface(0, d->dimx, d->dimy,
		32, RMASK, GMASK, BMASK, AMASK)))
			error(e, SDL_GetError());
		cams = cams->next;
	}
}

t_color		init_lit_scene(t_env *e, t_scene *s)
{
	t_lit	*l;
	t_prst	*p;

	l = s->lits;
	p = s->prsts;
	while (l)
	{
		s->amb_lit_c = rgbadd(s->amb_lit_c, l->color);
		while (p)
		{
			e->s.amb_lit_c = rgbadd(init_lit_scene(e, &(p->s)), e->s.amb_lit_c);
			p = p->next;
		}		l = l->next;
	}
	return (s->amb_lit_c);
}

void		init_scene(t_env *e, t_scene *s)
{
	init_cam(e, s);
	init_objs(e, s);
	init_grads(s);
	if (s->prsts)
		init_scene(e, &(s->prsts->s));

}

void		init(t_env *e)
{
	init_scene(e, &(e->s));
	init_lit_scene(e, &(e->s));
}
