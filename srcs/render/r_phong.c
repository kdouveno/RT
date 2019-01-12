/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_phong.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:24:37 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/12 18:10:28 by kdouveno         ###   ########.fr       */
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

t_color					phong(t_lit l, t_reslist *res, t_color lc)
{
	t_vec		lnc[3];
	t_color		diffuse;
	t_color		specular;
	t_color		obj_color;

	res->pert = (t_vec){0, 0, 0};
	obj_color = get_pt_color(*res->o, res->pt, &res->pert);
	lnc[0] = normalise(get_vector(res->pt, l.cpt));
	lnc[2] = res->cam;
	lnc[1] = res->pert.x == 0 && res->pert.y == 0 && res->pert.z == 0 ? res->n : rot(res->pert, get_rot(res->n, 0));
	diffuse = rgbpro(rgbmin(lc, rgbneg(obj_color)),
		diffuse_light(lnc) * res->o->mat.diff);
	specular = rgbpro(lc, spec_light(lnc) * res->o->mat.spec);
	return (rgbadd(rgbadd((t_color)AMASK, specular), diffuse));
}


t_color			soft_shadow(t_rendering *r, t_reslist *res, t_lit l, int rec)
{
	t_color		out;
	t_reslist	obj;
	t_pt		pts[6];
	int			i;

	out = (t_color)(unsigned)AMASK;
	if (rec > SHADOW_REC && !(i = 0))
		return (out);

	else if (l.radius != 0.0f && obj.o != res->o)
	{
		pts[0] = (t_pt){l.cpt.x + l.radius, l.cpt.y, l.cpt.z};
		pts[1] = (t_pt){l.cpt.x - l.radius, l.cpt.y, l.cpt.z};
		pts[2] = (t_pt){l.cpt.x, l.cpt.y + l.radius, l.cpt.z};
		pts[3] = (t_pt){l.cpt.x, l.cpt.y - l.radius, l.cpt.z};
		pts[4] = (t_pt){l.cpt.x, l.cpt.y, l.cpt.z + l.radius};
		pts[5] = (t_pt){l.cpt.x, l.cpt.y, l.cpt.z - l.radius};
		while (((i++) || 1) && (i < 6) | (int)(l.cpt = pts[i]).x)
			out = rgbadd(out, rgbpro(soft_shadow(r, res, l, rec + 1),
			SHADOW_C));
	}
	return (out);
}
