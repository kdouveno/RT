/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_raytrace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:51:19 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/10 17:30:12 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		refraction(t_rendering *r, t_reslist res, int bounce, t_ri *ri)
{
	double	n[3];
	t_vec	t;

	res.n = res.pert.x == 0 && res.pert.y == 0 && res.pert.z == 0 ? res.n : rot(res.pert, get_rot(res.n, 0));
	n[0] = ri->o ? ri->o->mat.n : 1 / res.o->mat.n; //nr
	n[1] = scalar_product(res.cam, res.n); // ci
	n[2] = sqrt(1 - sq(n[0]) * (1 - sq(n[1]))); // ct
	t = apply(rev_3d(vecpro(res.cam, n[0])), vecpro(res.n, n[0] * n[1] - n[2])); // T
	return (raytrace(r, (t_line){res.pt, t}, bounce, (t_ri){res.o, '+', ri}));
}

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
			vecpro(res.n, 2 * scalar_product(res.cam, res.n)))}, bounce + 1, ri), res.o->mat.refl);
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
