/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:51:19 by kdouveno          #+#    #+#             */
/*   Updated: 2018/11/12 16:59:21 by kdouveno         ###   ########.fr       */
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
		// printf("(%f)->", list->t);
		list = list->next;
	}
	// printf("(X)\n");
}

t_obj		*is_cind(t_obj *o, t_pt pt)
{
	t_objlist	*clpin;

	clpin = o->clipping;
	while (clpin)
	{
		if (g_ref[clpin->obj->type].isptin(pt, *clpin->obj))
			return (clpin->obj);
		clpin = clpin->next;
	}
	return (0);
}

t_obj		*is_tangible(t_obj *o, t_pt pt, t_obj *last)
{
	t_clip	*c;
	int		pc;
	t_obj	*pd;
	t_obj	*pdp;

	pd = is_cind(o, pt);
	pc = 1;
	pdp = pd && pd != last && (!last || o->b.clip) ? is_tangible(pd, pt, o) : pd;
	c = o->clips;
	if (!o->b.clip && !last)
		last = o;
	while (c){
		if (c->obj && c->obj != last && is_tangible(c->obj, pt, o) && g_ref[c->obj->type].isptin(pt, *c->obj))
		{
			pc = 0;
			break ;
		}
		c = c->next;
	}
	if (o->b.clip && pc == 1 && pd && pdp)
		return (pdp);
	if (!o->b.clip && pc)
		return (o);
	return (NULL);
}

// t_obj		*is_tangible(t_obj *o, t_pt pt)
// {
// 	t_clip	*c;
// 	int		pc;
// 	t_obj	*pd;
//
// 	// printf("tangible(id_%d, (%.1f, %.1f, %.1f))\n", o->id, pt.x, pt.y, pt.z);
// 	c = o->clips;
// 	pc = 1;
// 	while (c){
// 		// printf("clip: \033[32m %d\n", g_ref[c->obj->type].isptin(pt, *c->obj));
// 		if (c->obj && is_tangible(c->obj, pt) && g_ref[c->obj->type].isptin(pt, *c->obj))
// 		{
// 			// printf("\033[37m");
// 			pc = 0;
// 			break ;
// 		}
// 		// printf("\033[37m");
//
// 		c = c->next;
// 	}
// 	pd = is_cind(o, pt);
//
// 	// printf("bclip: %d, pc: %d, pd: %p, clipr %d\n", o->b.clip, pc, pd, o->b.clipr);
// 	if (o->b.clip && pc && pd && !o->b.clipr){
// 		// printf("- id_%d\n", pd->id);
// 		return (pd);}
// 	if (!o->b.clip && pc){
// 		// printf("- id_%d\n", o->id);
// 		return (o);}
// 	// printf("- NULL\n");
// 	return (NULL);
// }

t_reslist	get_touch(t_reslist *list, t_line line, t_pt campt)
{
	t_reslist	out;
	t_obj		*tmpobj;

	while (list)
	{
		list->pt = get_linept(line, list->t);

		if ((tmpobj = is_tangible(list->o, list->pt, NULL)) && !tmpobj->b.clip)
		{
			out = *list;
			out.o = tmpobj;
			out.cam = normalise(get_line(list->pt, campt).v);
			out.n = normalise(g_ref[list->o->type].norm(unrot(apply(vecpro(list->o->t, -1),
				list->pt), list->o->dir), *list->o, out.cam));
			return (out);
		}
		list = list->next;
	}
	return ((t_reslist){NULL, {}, {}, {}, 0, NULL});
}

t_reslist	intersec(t_rendering *r, t_line line)
{
	t_obj		*b;
	t_reslist	out;
	t_line		l;
	t_reslist	*list;

	list = NULL;

	out = (t_reslist){NULL, {}, {}, {}, 0, NULL};
	b = r->e->s.objs;
	while (b)
	{
		l.m = apply(vecpro(b->t, -1), line.m);
		l.m = unrot(l.m, b->dir);
		l.v = unrot(line.v, b->dir);
		g_ref[b->type].intersec(r->e, l, b, &list);
		b = b->next;
	}
	if (list)
		out = get_touch(list, line, r->c->t);
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

t_color texture_color(t_obj obj, t_pt pt)
{
	(void)obj;
	(void)pt;
	return (obj.mat.color);
}

t_color get_pt_color(t_obj obj, t_pt pt)
{
	if (obj.mat.txt)
		return (texture_color(obj, pt));
	else
		return (obj.mat.color);

}

t_color		ambiant_light(t_color amb_lit_c, t_color obj_color, double coef)
{
	t_color	out;

	out = (t_color)rgbmin(amb_lit_c, rgbneg(obj_color));
	return ((t_color)rgbpro(out, coef));
}

t_color		phong(t_lit l, t_reslist res)
{
	t_vec		lnc[3];
	t_color		diffuse;
	t_color		specular;
	t_color		ambient;
	t_color		obj_color;

	obj_color = get_pt_color(*res.o, res.pt);
	lnc[0] = normalise(get_line(res.pt, l.t).v);
	lnc[2] = res.cam;
	lnc[1] = res.n;
	diffuse = rgbpro(rgbmin(l.color, rgbneg(obj_color)),
		l.power * diffuse_light(lnc));
	specular = rgbpro(l.color, l.power * spec_light(lnc) * res.o->mat.spec);
	ambient = (t_color)rgbpro(obj_color, AMB_L);
	return (rgbadd(rgbadd(rgbadd((t_color)AMASK, specular), diffuse), ambient));
}

t_color		lites(t_rendering *r, t_reslist res)
{
	t_lit		*l;
	t_color		out;
	int			i;

	out = (t_color) (unsigned)AMASK;
	l = r->e->s.lits;
	while (l)
	{
		if (intersec(r, get_line(l->t, res.pt)).t > 0.9999 && (i = 0) == 0)
			out = rgbadd(out, phong(*l, res));
		else
			out = rgbadd(out,
			ambiant_light(r->e->s.amb_lit_c, get_pt_color(*res.o, res.pt), AMB_L));
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
	res = intersec(r, l);
	if (res.o)
		out.i |= lites(r, res).i;
	return (out);
}
