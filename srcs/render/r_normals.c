/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_normals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:31:48 by kdouveno          #+#    #+#             */
/*   Updated: 2018/11/22 11:17:22 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	cylinder_norm(t_pt pt, t_obj obj, t_vec v)
{
	t_vec	out;
	double	tmp;

	(void)v;
	out = rot((t_vec){pt.x, pt.y, 0}, obj.dir);
	if ((tmp = scalar_product(normalise(out), v)) > 1 || tmp < 0)
		out = vec_rev(out);
	return (out);
}

t_vec	cone_norm(t_pt pt, t_obj obj, t_vec v)
{
	t_vec	out;
	double	tmp;

	(void)v;
	out = rot((t_vec){pt.x, pt.y, -sq(tan(obj.v[0] )) * pt.z}, obj.dir);
	if ((tmp = scalar_product(normalise(out), v)) > 1 || tmp < 0)
		out = vec_rev(out);
	return (out);
}

t_vec	sphere_norm(t_pt pt, t_obj obj, t_vec v)
{
	t_vec	out;
	double	tmp;

	(void)obj;
	out = rot(pt, obj.dir);
	if ((tmp = scalar_product(normalise(out), v)) > 1 || tmp < 0)
		out = vec_rev(out);
	return (out);
}

t_vec	plane_norm(t_pt pt, t_obj obj, t_vec v)
{
	t_vec	out;
	double	tmp;

	out = rot((t_vec){1, 0, 0}, obj.dir);
	if ((tmp = scalar_product(normalise(out), v)) > 1 || tmp < 0)
		out = vec_rev(out);
	(void)pt;
	return (out);
}

t_vec	cuboid_norm(t_pt pt, t_obj obj, t_vec v)
{
	t_line	d;
	double	d1;
	double	t;
	t_vec	out;
	int i;

	i = 0;
	d = (t_line){pt, v};
	while (i < 2)
	{
		d1 = ((i ? -1 : 1) * obj.v[0] - d.m.x) / d.v.x;
		if (fabs(d1) < fabs(t) && ((t = d1) || 1))
			out = (t_vec){1, 0, 0};
		d1 = ((i ? -1 : 1) * obj.v[1] - d.m.y) / d.v.y;
		if (fabs(d1) < fabs(t) && ((t = d1) || 1))
			out = (t_vec){0, 1, 0};
		d1 = ((i ? -1 : 1) * obj.v[2] - d.m.z) / d.v.z;
		if (fabs(d1) < fabs(t) && ((t = d1) || 1))
			out = (t_vec){0, 0, 1};
		i++;
	}
	out = rot(out, obj.dir);
	if ((t = scalar_product(normalise(out), v)) > 1 || t < 0)
		out = vec_rev(out);
	return (out);
}
