/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_raytrace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:51:19 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/11 16:58:21 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		refraction(t_rendering *r, t_reslist res, int bounce, t_ri ri)
{
	float	n[3];
	double	c[2];
	t_vec	t;

	res.cam = rev_3d(res.cam);
	n[1] = ri.n;
	n[2] = res.o->mat.n;
	ri.n = n[2];
	n[0] = n[1] / n[2];
	printf("%f\n", n[0]);
	c[0] = scalar_product(res.cam, res.n);
	c[1] = sqrt(1 - sq(n[0]) * (1 - sq(c[0])));
	t = apply(vecpro(res.cam, n[0]), vecpro(res.n, n[0] * c[0] - c[1]));
	return (raytrace(r, (t_line){res.pt, t}, bounce, &ri));
}

t_color		lites(t_rendering *r, t_reslist res, int bounce, t_ri *ri)
{
	t_lit		*l;
	t_color		out;

	out = (t_color)(unsigned)AMASK;
	l = r->e->s.lits;
	while (l)
	{
		out = rgbadd(out, soft_shadow(r, res, *l, 1));
		if (res.o->mat.refl && bounce < REC_BOUNCE)
		{
			out = rgbmid(out, raytrace(r, (t_line){res.pt,
			apply(rev_3d(res.cam), vecpro(res.n, 2
				* scalar_product(res.cam, res.n)))}, bounce + 1, ri),
				res.o->mat.refl);
		}
		if (res.o->mat.tr)
			out = rgbmid(out, refraction(r, res, bounce,
				(!ri ? (t_ri){1.0, '.', NULL} : *ri)), res.o->mat.tr);
		l = l->next;
	}
	return (filter(r, out));
}

/*
**	renvoie la couleur du pixel a afficher pour un rayon de droite
*/

t_color		raytrace(t_rendering *r, t_line l, int bounce, t_ri *ri)
{
	t_reslist	res;
	t_color		out;

	out = (t_color)(unsigned)AMASK;
	res = intersec(r, l);
	if (res.o)
		out.i |= lites(r, res, bounce, ri).i;
	return (out);
}
