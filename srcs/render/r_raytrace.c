/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_raytrace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:51:19 by kdouveno          #+#    #+#             */
/*   Updated: 2018/12/12 11:31:11 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		soft_shadow(t_rendering *r, t_reslist res, t_lit l, int rec)
{
	t_color		out;
	t_reslist	obj;

	out = (t_color) (unsigned)AMASK;
	if (rec > SHADOW_REC)
		return (out);
	out = rgbadd(out,
		ambiant_light(r->e->s.amb_lit_c, get_pt_color(*res.o, res.pt), AMB_L));
	if ((obj = intersec(r, get_line(l.t, res.pt))).t > 1 - PRE)
		out = rgbadd(out, phong((t_lit){{l.t.x, l.t.y, l.t.z}, l.power, l.radius, l.color, l.b, l.id, l.next}, res));
	else if (l.radius != 0.0f && obj.o != res.o)
	{
		out = rgbadd(out, rgbpro(soft_shadow(r, res, (t_lit){{l.t.x, l.t.y, l.t.z + l.radius}, l.power, l.radius, l.color, l.b, l.id, l.next}, rec + 1), SHADOW_C));
		out = rgbadd(out, rgbpro(soft_shadow(r, res, (t_lit){{l.t.x, l.t.y, l.t.z - l.radius}, l.power, l.radius, l.color, l.b, l.id, l.next}, rec + 1), SHADOW_C));
		out = rgbadd(out, rgbpro(soft_shadow(r, res, (t_lit){{l.t.x, l.t.y + l.radius, l.t.z}, l.power, l.radius, l.color, l.b, l.id, l.next}, rec + 1), SHADOW_C));
		out = rgbadd(out, rgbpro(soft_shadow(r, res, (t_lit){{l.t.x, l.t.y - l.radius, l.t.z}, l.power, l.radius, l.color, l.b, l.id, l.next}, rec + 1), SHADOW_C));
		out = rgbadd(out, rgbpro(soft_shadow(r, res, (t_lit){{l.t.x + l.radius, l.t.y, l.t.z}, l.power, l.radius, l.color, l.b, l.id, l.next}, rec + 1), SHADOW_C));
		out = rgbadd(out, rgbpro(soft_shadow(r, res, (t_lit){{l.t.x - l.radius, l.t.y, l.t.z}, l.power, l.radius, l.color, l.b, l.id, l.next}, rec + 1), SHADOW_C));
	}
	return (out);
}

t_color		lites(t_rendering *r, t_reslist res, int bounce)
{
	t_lit		*l;
	t_color		out;

	out = (t_color) (unsigned)AMASK;
	l = r->e->s.lits;
	while (l)
	{
		out = rgbadd(out, soft_shadow(r, res, *l, 1));
		if (res.o->mat.refl && bounce < REC_BOUNCE)
		{
			out = rgbmid(out, raytrace(r, (t_line){res.pt, apply(vec_rev(res.cam),
			vecpro(res.n, 2 * scalar_product(res.cam, res.n)))}, bounce + 1), res.o->mat.refl);
		}
		l = l->next;
	}
	return (out);
}

/*
**	renvoie la couleur du pixel a afficher pour un rayon de droite
*/

t_color		raytrace(t_rendering *r, t_line l, int bounce)
{
	t_reslist	res;
	t_color		out;

	out = (t_color)(unsigned)AMASK;
	res = intersec(r, l);
	if (res.o)
		out.i |= lites(r, res, bounce).i;
	return (out);
}
