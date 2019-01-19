/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_raytrace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:51:19 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/19 16:30:32 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_color		lites(t_rendering *r, t_reslist res, int bounce, t_ri *ri)
{
	t_lit		*l;
	t_color		out;
	t_vec		n;

	out = (t_color)(unsigned)AMASK;
	l = r->e->s.lits;
	while (l)
	{
		out = rgbadd(out, soft_shadow(r, &res, *l, 1));
		if (res.o->mat.refl && bounce < REC_BOUNCE)
		{
			n = res.pert.x == 0 && res.pert.y == 0 && res.pert.z == 0 ?
			res.n : rot(res.pert, get_rot(res.n, 0));
			out = rgbmid(out, raytrace(r, (t_line){res.pt,
				apply(rev_3d(res.cam), vecpro(n,
				2 * scalar_product(res.cam, n)))}, bounce + 1, *ri),
				res.o->mat.refl);
		}
		if (res.o->mat.tr)
		{
			out = rgbmid(out, refraction(r, res, bounce, ri), res.o->mat.tr);
		}
		l = l->next;
	}
	return (filter(r, out));
}

/*
**	renvoie la couleur du pixel a afficher pour un rayon (une droite)
*/

t_color				raytrace(t_rendering *r, t_line l, int bounce, t_ri ri)
{
	t_reslist	res;
	t_color		out;

	out = (t_color)(unsigned)AMASK;
	res = intersec(r, l);
	if (res.o)
		out.i |= lites(r, res, bounce, &ri).i;
	return (out);
}
