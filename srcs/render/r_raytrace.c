/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_raytrace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:51:19 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/11 12:58:52 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"



t_color		lites(t_rendering *r, t_reslist res, int bounce, t_ri *ri)
{
	t_lit		*l;
	t_color		out;

	out = (t_color) (unsigned)AMASK;
	l = r->e->s.lits;
	while (l)
	{
		out = rgbadd(out, soft_shadow(r, &res, *l, 1));
		if (res.o->mat.refl && bounce < REC_BOUNCE)
		{
			out = rgbmid(out, raytrace(r, (t_line){res.pt, apply(rev_3d(res.cam),
			vecpro(res.n, 2 * scalar_product(res.cam, res.n)))}, bounce + 1, *ri), res.o->mat.refl);
		}
		if (res.o->mat.tr)
		{
			out = rgbmid(out, refraction(r, res, bounce, ri), res.o->mat.tr);
		}
		l = l->next;
	}
	return (out);
}

/*
**	renvoie la couleur du pixel a afficher pour un rayon (une droite)
*/

t_color		raytrace(t_rendering *r, t_line l, int bounce, t_ri ri)
{
	t_reslist	res;
	t_color		out;

	out = (t_color)(unsigned)AMASK;
	res = intersec(r, l);
	if (res.o)
		out.i |= lites(r, res, bounce, &ri).i;
	return (out);
}