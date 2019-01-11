/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_intersect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:25:50 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/11 15:45:41 by kdouveno         ###   ########.fr       */
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

inline static t_obj		*is_cind(t_obj *o, t_pt pt)
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

static t_obj			*is_tangible(t_obj *o, t_pt pt, t_obj *last)
{
	t_clip	*c;
	int		pc;
	t_obj	*d;
	t_obj	*p;

	d = is_cind(o, pt);
	pc = 1;
	p = d && d != last && (!last || o->b.clip) ? is_tangible(d, pt, o) : d;
	c = o->clips;
	if (!o->b.clip && !last)
		last = o;
	while (c){
		if (c->obj && c->obj != last && is_tangible(c->obj, pt, o) &&
		g_ref[c->obj->type].isptin(pt, *c->obj))
		{
			pc = 0;
			break ;
		}
		c = c->next;
	}
	if (o->b.clip && pc == 1 && d && p)
		return (p);
	if (!o->b.clip && pc)
		return (o);
	return (NULL);
}

inline static t_reslist	get_touch(t_reslist *list, t_line line)
{
	t_reslist	out;
	t_obj		*tmpobj;
	double		tmp;

	while (list)
	{
		list->pt = get_linept(line, list->t);
		if ((tmpobj = is_tangible(list->o, list->pt, NULL)) && !tmpobj->b.clip)
		{
			out = *list;
			out.o = tmpobj;
			out.co = list->o;
			out.cam = normalise(get_line(list->pt, line.m).v);
			out.tn = normalise(g_ref[list->o->type].norm(rtrans_pt(list->pt, &list->o->m), *list->o, out.cam));
			out.n = ((tmp = scalar_product(normalise(out.tn), out.cam)) > 1 || tmp < 0) ? rev_3d(out.tn) : out.tn;
			free(list);
			return (out);
		}
		list = list->next;
	}
	free(list);
	return ((t_reslist){NULL, NULL, {}, {}, {}, {}, {}, 0, NULL});
}

t_reslist				intersec(t_rendering *r, t_line line)
{
	t_obj		*b;
	t_reslist	out;
	t_line		l;
	t_reslist	*list;

	list = NULL;
	out = (t_reslist){NULL, NULL, {}, {}, {}, {}, {}, 0, NULL};
	b = r->e->s.objs;
	while (b)
	{
		if (!g_ref[b->type].intersec
		|| (!g_ref[b->type].norm)
		|| (!g_ref[b->type].isptin))
		{
			b = b->next;
			continue ;
		}
		l = rtrans_line(line, &b->m);
		g_ref[b->type].intersec(r->e, l, b, &list);
		b = b->next;
	}
	if (list)
		out = get_touch(list, line);
	return (out);
}
