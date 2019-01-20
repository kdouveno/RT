/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_phong.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:24:37 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/20 12:29:58 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	diffuse_light(t_vec lnc[3])
{
	double	out;

	out = scalar_product(lnc[0], lnc[1]);
	return (out);
}

static double	spec_light(t_vec lnc[3])
{
	double	out;
	t_vec	h;

	h = normalise((t_vec){(lnc[0].x + lnc[2].x) / 2, (lnc[0].y + lnc[2].y) / 2,
		(lnc[0].z + lnc[2].z) / 2});
	out = pow(scalar_product(h, lnc[1]), 100);
	return (out);
}

static t_color	ambiant_light(t_color amb_lit_c, t_color obj_color, double coef)
{
	t_color	out;

	out = (t_color)rgbmin(amb_lit_c, rgbneg(obj_color));
	return ((t_color)rgbpro(out, coef));
}

t_color			phong(t_lit l, t_reslist *res, t_color lc)
{
	t_vec		lnc[3];
	t_color		diffuse;
	t_color		specular;
	t_color		obj_color;

	res->pert = (t_vec){0, 0, 0};
	obj_color = get_pt_color(*res->o, res->pt, &res->pert);
	lnc[0] = normalise(get_vector(res->pt, l.cpt));
	lnc[2] = res->cam;
	lnc[1] = res->pert.x == 0 && res->pert.y == 0 && res->pert.z == 0 ? res->n
		: rot(res->pert, get_rot(res->n, 0));
	diffuse = rgbpro(rgbmin(lc, rgbneg(obj_color)),
		l.power * diffuse_light(lnc) * res->o->mat.diff);
	specular = rgbpro(lc, l.power * spec_light(lnc) * res->o->mat.spec);
	return (rgbadd(rgbadd((t_color)AMASK, specular), diffuse));
}

t_color			soft_shadow(t_rendering *r, t_reslist *res, t_lit l, int rec)
{
	t_color		out;
	t_color		tmp;

	out = (t_color)(unsigned)AMASK;
	if (rec > SHADOW_REC)
		return (out);
	tmp = catch_light(r, &l, res);
	if (tmp.p.a != 1)
	{
		out = rgbadd(out, phong(l, res, tmp));
		out = rgbadd(out,
			ambiant_light(r->e->s.amb_lit_c,
				get_pt_color(*res->o, res->pt, NULL), AMB_L));
	}
	else if (l.radius != 0.0f && tmp.p.a == 1)
		out = rgbadd(soft_shadow2(r, res, l, rec), out);
	else
		out = rgbadd(out,
			ambiant_light(r->e->s.amb_lit_c,
				get_pt_color(*res->o, res->pt, &res->pert), AMB_L));
	return (out);
}
