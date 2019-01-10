/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_normals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:31:48 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/10 17:07:58 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	cylinder_norm(t_pt pt, t_obj obj, t_vec v)
{
	t_vec	out;
	double	tmp;

	(void)v;
	out = trans_vec((t_vec){pt.x, pt.y, 0}, &obj.m);
	if ((tmp = scalar_product(normalise(out), v)) > 1 || tmp < 0)
		out = rev_3d(out);
	return (out);
}

t_vec	cone_norm(t_pt pt, t_obj obj, t_vec v)
{
	t_vec	out;
	double	tmp;

	(void)v;
	out = trans_vec((t_vec){pt.x, pt.y, -sq(tan(obj.v[0] )) * pt.z}, &obj.m);
	if ((tmp = scalar_product(normalise(out), v)) > 1 || tmp < 0)
		out = rev_3d(out);
	return (out);
}

t_vec	sphere_norm(t_pt pt, t_obj obj, t_vec v)
{
	t_vec	out;
	double	tmp;

	(void)obj;
	out = trans_vec(pt, &obj.m);
	if ((tmp = scalar_product(normalise(out), v)) > 1 || tmp < 0)
		out = rev_3d(out);
	return (out);
}

t_vec	plane_norm(t_pt pt, t_obj obj, t_vec v)
{
	t_vec	out;
	double	tmp;

	out = trans_vec((t_vec){1, 0, 0}, &obj.m);
	if ((tmp = scalar_product(normalise(out), v)) > 1 || tmp < 0)
		out = rev_3d(out);
	(void)pt;
	return (out);
}

t_vec	cuboid_norm(t_pt pt, t_obj obj, t_vec v)
{
	t_line	d;
	double	d1;
	double	tmp;
	t_vec	out;
	int i;

	i = 0;
	d = (t_line){pt, v};
	while (i < 2)
	{
		d1 = ((i ? -1 : 1) * obj.v[0] - d.m.x) / d.v.x;
		if (fabs(d1) < fabs(tmp) && ((tmp = d1) || 1))
			out = (t_vec){1, 0, 0};
		d1 = ((i ? -1 : 1) * obj.v[1] - d.m.y) / d.v.y;
		if (fabs(d1) < fabs(tmp) && ((tmp = d1) || 1))
			out = (t_vec){0, 1, 0};
		d1 = ((i ? -1 : 1) * obj.v[2] - d.m.z) / d.v.z;
		if (fabs(d1) < fabs(tmp) && ((tmp = d1) || 1))
			out = (t_vec){0, 0, 1};
		i++;
	}
	out = trans_vec(out, &obj.m);
	if ((tmp = scalar_product(normalise(out), v)) > 1 || tmp < 0)
		out = rev_3d(out);
	return (out);
}
