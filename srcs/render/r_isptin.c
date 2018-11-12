/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_isptin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:44:37 by kdouveno          #+#    #+#             */
/*   Updated: 2018/11/12 17:19:29 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		sphere_isptin(t_pt pt, t_obj o)
{
	return (dist(pt, o.t) <= o.v[0] + PRE);
}

int		cylinder_isptin(t_pt pt, t_obj o)
{
	pt = unrot(apply(vecpro(o.t, -1), pt), o.dir);
	pt.z = 0;
	return (get_norm(pt) <= o.v[0] + PRE);
}

int		cone_isptin(t_pt pt, t_obj o)
{
	double	z;
	pt = unrot(apply(vecpro(o.t, -1), pt), o.dir);
	z = fabs(pt.z);
	pt.z = 0;
	return (get_norm(pt) <= tan(o.v[0]) * z + PRE);
}

int		plane_isptin(t_pt pt, t_obj o)
{
	pt = unrot(apply(vecpro(o.t, -1), pt), o.dir);
	return (pt.x > 0);
}

int		cuboid_isptin(t_pt pt, t_obj o)
{
	pt = unrot(apply(vecpro(o.t, -1), pt), o.dir);
	// printf("cuboid is in %d\n", pt.x <= o.v[0] + PRE && pt.x >= -o.v[0] - PRE
			// && pt.y <= o.v[1] + PRE && pt.y >= -o.v[1] - PRE
			// && pt.z <= o.v[2] + PRE && pt.z >= -o.v[2] - PRE);
	return (pt.x <= o.v[0] + PRE && pt.x >= -o.v[0] - PRE
			&& pt.y <= o.v[1] + PRE && pt.y >= -o.v[1] - PRE
			&& pt.z <= o.v[2] + PRE && pt.z >= -o.v[2] - PRE);
}
