/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_isptin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:44:37 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/11 16:05:17 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		sphere_isptin(t_pt pt, t_obj o)
{
	pt = rtrans_pt(pt, &o.m);
	return (get_norm(pt) <= o.v[0] + PRE);
}

int		cylinder_isptin(t_pt pt, t_obj o)
{
	pt = rtrans_pt(pt, &o.m);
	pt.z = 0;
	return (get_norm(pt) <= o.v[0] + PRE);
}

int		cone_isptin(t_pt pt, t_obj o)
{
	double	z;

	pt = rtrans_pt(pt, &o.m);
	z = fabs(pt.z);
	pt.z = 0;
	return (get_norm(pt) <= tan(o.v[0]) * z + PRE);
}

int		plane_isptin(t_pt pt, t_obj o)
{
	pt = rtrans_pt(pt, &o.m);
	return (pt.x > 0);
}

int		cuboid_isptin(t_pt pt, t_obj o)
{
	pt = rtrans_pt(pt, &o.m);
	return (pt.x <= o.v[0] + PRE && pt.x >= -o.v[0] - PRE
			&& pt.y <= o.v[1] + PRE && pt.y >= -o.v[1] - PRE
			&& pt.z <= o.v[2] + PRE && pt.z >= -o.v[2] - PRE);
}
