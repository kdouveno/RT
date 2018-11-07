/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:31:48 by kdouveno          #+#    #+#             */
/*   Updated: 2018/11/04 15:24:01 by kdouveno         ###   ########.fr       */
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
	out = rot((t_vec){pt.x, pt.y, -sq(tan(obj.v1)) * pt.z}, obj.dir);
	if ((tmp = scalar_product(normalise(out), v)) > 1 || tmp < 0)
		out = vec_rev(out);
	return (out);
}

t_vec	sphere_norm(t_pt pt, t_obj obj, t_vec v)
{
	t_vec	out;
	double	tmp;

	(void)v;
	(void)obj;
	out = (t_vec)pt;
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
