/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_phong.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:24:37 by kdouveno          #+#    #+#             */
/*   Updated: 2018/12/12 11:25:40 by kdouveno         ###   ########.fr       */
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
