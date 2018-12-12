/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 14:13:40 by gperez            #+#    #+#             */
/*   Updated: 2018/12/12 16:42:56 by kdouveno         ###   ########.fr       */
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
		grads->m.rot = get_vector(grads->m.t, grads->m.rot);
		grads->r = get_rot(grads->m.rot, 0);
		grads = grads->next;
	}
}

void 		init_objs(t_env *e, t_scene *s)
{
	t_obj	*objs;

	objs = s->objs;
	while (objs)
	{
		if (objs->m.r >= 0)
			objs->m.rot = get_rot(objs->m.rot, objs->m.r);
		else
			objs->m.rot = (t_three_d){rad(objs->m.rot.x),
			rad(objs->m.rot.y), rad(objs->m.rot.z)};
		if (objs->type == CONE)
			objs->v[0] = rad(objs->v[0]);
		check_clip_loop(e, objs, objs, 0);
		objs = objs->next;
	}
}

void		init_cam_vecs(t_cam *cams)
{
	double			step;
	t_cam_render	*d;

	d = &cams->data;
	step = 1;
	d->pt_ul = cams->m.t;
	if (d->para)
	{
		step = d->fov / d->dimx;
		d->vp_ul = rot((t_vec){1,
			0, 0}, cams->m.rot);
		d->pt_ul = apply(rot((t_vec){0, d->fov / 2, d->dimy * step / 2},
			cams->m.rot), d->pt_ul);
	}
	else
		d->vp_ul = rot((t_vec){(double)(d->dimx / 2) / tan(rad(d->fov) / 2),
			d->dimx / 2, d->dimy / 2}, cams->m.rot);
	d->x = rot((t_vec){0, -step, 0}, cams->m.rot);
	d->y = rot((t_vec){0, 0, -step}, cams->m.rot);
	d->xy = rot((t_vec){0, step * (d->dimx - 1), -step}, cams->m.rot);
}

void		init_cam(t_env *e, t_scene *s)
{
	t_cam			*cams;
	t_cam_render	*d;

	cams = s->cams;
	while (cams)
	{
		d = &cams->data;
		if (cams->m.r >= 0)
			cams->m.rot = get_rot(get_vector(cams->m.t, cams->m.rot), cams->m.r);
		else
			cams->m.rot = (t_three_d){rad(cams->m.rot.x),
			rad(cams->m.rot.y), rad(cams->m.rot.z)};
		d->dimx = DIMX;
		d->dimy = DIMY;
		init_cam_vecs(cams);
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
		}
		l = l->next;
	}
	return (s->amb_lit_c);
}

int			nb_light(t_scene *s)
{
	t_lit	*l;
	int		c;

	c = 0;
	l = s->lits;
	while (l)
	{
		c++;
		l = l->next;
	}
	return (c);
}

void		init_light_auto(t_scene *s)
{
	t_lit	*l;
	int		c;

	c = nb_light(s);
	if (c == 1)
		return;
	l = s->lits;
	while (l)
	{
		l->power = l->power / c;
		l = l->next;
	}
}

void		init_scene(t_env *e, t_scene *s)
{
	if (s->auto_l)
		init_light_auto(s);
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
	if (e->glb.d)
		debug(e->s, 1);
}
