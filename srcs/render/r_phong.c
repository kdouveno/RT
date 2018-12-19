/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_phong.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:24:37 by kdouveno          #+#    #+#             */
/*   Updated: 2018/12/12 17:25:41 by kdouveno         ###   ########.fr       */
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

	h = normalise((t_vec){
		(lnc[0].x + lnc[2].x) / 2,
		(lnc[0].y + lnc[2].y) / 2,
		(lnc[0].z + lnc[2].z) / 2
	});
	out = pow(scalar_product(h, lnc[1]), 100);
	return (out);
}

static t_color	ambiant_light(t_color amb_lit_c, t_color obj_color, double coef)
{
	t_color	out;

	out = (t_color)rgbmin(amb_lit_c, rgbneg(obj_color));
	return ((t_color)rgbpro(out, coef));
}

t_color					phong(t_lit l, t_reslist res)
{
	t_vec		lnc[3];
	t_color		diffuse;
	t_color		specular;
	t_color		obj_color;

	res.pert = (t_vec){0, 0, 0};
	obj_color = get_pt_color(*res.o, res.pt, &res.pert);
	lnc[0] = normalise(apply(get_line(res.pt, l.m.t).v, res.pert));
	lnc[2] = res.cam;
	lnc[1] = res.n;
	diffuse = rgbpro(rgbmin(l.color, rgbneg(obj_color)),
		l.power * diffuse_light(lnc));
	specular = rgbpro(l.color, l.power * spec_light(lnc) * res.o->mat.spec);
	return (rgbadd(rgbadd((t_color)AMASK, specular), diffuse));
}

t_color			soft_shadow(t_rendering *r, t_reslist res, t_lit l, int rec)
{
	t_color		out;
	t_reslist	obj;
	t_pt		pts[6];
	int			i;

	out = (t_color) (unsigned)AMASK;
	if (rec > SHADOW_REC && !(i = 0))
		return (out);
	out = rgbadd(out,
		ambiant_light(r->e->s.amb_lit_c, get_pt_color(*res.o, res.pt, &res.pert), AMB_L));
	if ((obj = intersec(r, get_line(l.m.t, res.pt))).t > 1 - PRE)
		out = rgbadd(out, phong(l, res));
	else if (l.radius != 0.0f && obj.o != res.o)
	{
		pts[0] = (t_pt){l.m.t.x + l.radius, l.m.t.y, l.m.t.z};
		pts[1] = (t_pt){l.m.t.x - l.radius, l.m.t.y, l.m.t.z};
		pts[2] = (t_pt){l.m.t.x, l.m.t.y + l.radius, l.m.t.z};
		pts[3] = (t_pt){l.m.t.x, l.m.t.y - l.radius, l.m.t.z};
		pts[4] = (t_pt){l.m.t.x, l.m.t.y, l.m.t.z + l.radius};
		pts[5] = (t_pt){l.m.t.x, l.m.t.y, l.m.t.z - l.radius};
		while (((i++) || 1) && (i < 6) | (int)(l.m.t = pts[i]).x)
			out = rgbadd(out, rgbpro(soft_shadow(r, res, l, rec + 1),
			SHADOW_C));
	}
	return (out);
}
