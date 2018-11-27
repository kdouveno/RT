/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 14:13:40 by gperez            #+#    #+#             */
/*   Updated: 2018/11/27 18:11:31 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void check_clip_loop(t_env *e, t_obj *o, t_obj *original, int i)
{
	t_objlist	*clpin;

	if (i && o == original)
		error(e, CLIP_CIRCLE_ERROR);
	i = 1;
	clpin = o->clipping;
	while (clpin)
	{
		check_clip_loop(e, clpin->obj, original, i);
		clpin = clpin->next;
	}
}

void		init_grad(t_scene *s)
{
	t_grad	*grads;

	grads = s->grads;
	while (grads)
	{
		grads->dir = get_vector(grads->t, grads->dir);
		grads->r = get_rot(grads->dir, 0);
		grads = grads->next;
	}
}

void 		init_objs(t_env *e, t_scene *s)
{
	t_obj	*objs;

	objs = s->objs;
	while (objs)
	{
		if (objs->r >= 0)
			objs->dir = get_rot(objs->dir, objs->r);
		else
			objs->dir = (t_three_d){rad(objs->dir.x),
			rad(objs->dir.y), rad(objs->dir.z)};
		if (objs->type == CONE)
			objs->v[0] = rad(objs->v[0]);
		check_clip_loop(e, objs, objs, 0);
		objs = objs->next;
	}
}

void		init_cam(t_env *e, t_scene *s)
{
	t_cam			*cams;
	t_cam_render	*d;

	cams = s->cams;
	while (cams)
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
	init_objs(e, s);
	init_cam(e, s);
	init_grad(s);
	if (s->prsts)
		init_scene(e, &(s->prsts->s));
}

void		init(t_env *e)
{
	init_scene(e, &(e->s));
	init_lit_scene(e, &(e->s));
}
