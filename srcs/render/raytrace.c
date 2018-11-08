/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:51:19 by kdouveno          #+#    #+#             */
/*   Updated: 2018/11/08 19:12:43 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	calcule l'intersection et renvoi le t_intersec
**	out(b, t) avec:
**	b l'objet traverse
**	t la distance entre la camera et le point d'intersection exprime en vecteur
**		directeur de la droite line (l.v)
*/
void	print_reslist(t_reslist *list)
{
	while (list)
	{
		printf("(%f)->", list->t);
		list = list->next;
	}
	printf("(X)\n");
}

int			is_tangible(t_obj *o, t_pt pt)
{
	t_clip	*c;
	int		out;

	c = o->clips;
	out = 1;
	while (c)
	{
		if (is_tangible(c->o, pt,))
			continue ;
		out = 0;
		break ;
	}
	if (o->b.clip)
	{
		if (is_cind(o->clipping, pt))
			return (o->b.clipr);
		else
			return (0);
	}
	else
	{
		if (is_dinc(o->clips, pt))
			return (0)
	}
}

t_reslist	get_touch(t_reslist *list, t_line line)
{
	t_reslist out;
	list->pt = get_linept(line, list->t);
	out = *list;
	while (list)
	{
		list->pt = get_linept(line, list->t);
		is_tangible(list->o, list->pt);
		list = list->next;
	}
	return (out);
}

t_reslist	intersec(t_env *e, t_line line)
{
	t_obj		*b;
	t_reslist	out;
	t_line		l;
	t_reslist	*list;

	list = NULL;
	out = (t_reslist){0, {}, NULL, NULL};
	b = e->s.objs;
	while (b)
	{
		l.m = apply(vecpro(b->t, -1), line.m);
		l.m = unrot(l.m, b->dir);
		l.v = unrot(line.v, b->dir);
		g_ref[b->type].intersec(e, l, b, &list);
		b = b->next;
	}
	if (list)
		out = get_touch(list, line);
	return (out);
}

double		diffuse_light(t_vec lnc[3])
{
	double	out;

	out = scalar_product(lnc[0], lnc[1]);
	return (out);
}

double		spec_light(t_vec lnc[3])
{
	double	out;
	t_vec	h;

	h = normalise((t_vec){
		(lnc[0].x + lnc[2].x) / 2,
		(lnc[0].y + lnc[2].y) / 2,
		(lnc[0].z + lnc[2].z) / 2
	});
	out = pow(scalar_product(h, lnc[1]), 100);
	return (out);
}

t_color get_pt_color(t_obj obj)
{
	return (obj.mat.color);
}

t_color		phong(t_rendering *r, t_pt pt, t_lit l, t_obj o)
{
	t_vec		lnc[3];
	t_color		diffuse;
	t_color		specular;
	t_color		ambient;
	t_color		obj_color;

	obj_color = get_pt_color(o);
	lnc[0] = normalise(get_line(pt, l.t).v);
	lnc[2] = normalise(get_line(pt, r->c->t).v);
	lnc[1] = normalise(g_ref[o.type].norm(unrot(apply(vecpro(o.t, -1),
	pt), o.dir), o, lnc[2]));
	diffuse = rgbpro(rgbmin(l.color, rgbneg(obj_color)),
		l.power * diffuse_light(lnc));
	specular = rgbpro(l.color, l.power * spec_light(lnc) * o.mat.spec);
	ambient = (t_color)rgbpro(obj_color, AMB_L);
	return (rgbadd(rgbadd(rgbadd((t_color)AMASK, specular), diffuse), ambient));
}

t_color		lites(t_rendering *r, t_pt pt, t_obj obj)
{
	t_lit		*l;
	t_color		out;
	int			i;

	out = (t_color) (unsigned)AMASK;
	l = r->e->s.lits;
	while (l)
	{
		if (intersec(r->e, get_line(l->t, pt)).t > 0.9999 && (i = 0) == 0)
			out = rgbadd(out, phong(r, pt, *l, obj));
		else
			out = rgbadd(out, rgbpro(get_pt_color(obj), AMB_L));
		l = l->next;
	}
	return (out);
}

/*
**	renvoie la couleur du pixel a afficher pour un rayon de droite
*/

t_color		raytrace(t_rendering *r, t_line l)
{
	t_reslist	res;
	t_color		out;

	pthread_mutex_unlock(&r->lock);
	out = (t_color)(unsigned)AMASK;
	res = intersec(r->e, l);
	if (res.o)
		out.i |= lites(r, res.pt, *res.o).i;
	return (out);
}
