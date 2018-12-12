/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_phong.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:24:37 by kdouveno          #+#    #+#             */
/*   Updated: 2018/12/12 11:43:14 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	t_color		obj_color;

	obj_color = get_pt_color(*res.o, res.pt);
	lnc[0] = normalise(get_line(res.pt, l.t).v);
	lnc[2] = res.cam;
	lnc[1] = res.n;
	diffuse = rgbpro(rgbmin(l.color, rgbneg(obj_color)),
		l.power * diffuse_light(lnc));
	specular = rgbpro(l.color, l.power * spec_light(lnc) * res.o->mat.spec);
	return (rgbadd(rgbadd((t_color)AMASK, specular), diffuse));
}

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
