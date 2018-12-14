/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_3dobj_ops.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 17:02:52 by kdouveno          #+#    #+#             */
/*   Updated: 2018/04/06 15:33:26 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo3d.h"

t_3d	xrot(t_3d td, double a)
{
	t_3d out;

	out.x = td.x;
	out.y = cos(a) * td.y - sin(a) * td.z;
	out.z = sin(a) * td.y + cos(a) * td.z;
	return (out);
}

t_3d	yrot(t_3d td, double a)
{
	t_3d out;

	out.x = cos(a) * td.x + sin(a) * td.z;
	out.y = td.y;
	out.z = cos(a) * td.z - sin(a) * td.x;
	return (out);
}

t_3d	zrot(t_3d td, double a)
{
	t_3d out;

	out.x = cos(a) * td.x - sin(a) * td.y;
	out.y = sin(a) * td.x + cos(a) * td.y;
	out.z = td.z;
	return (out);
}

t_3d	rot(t_3d td, t_rot r)
{
	td = xrot(td, r.x);
	td = yrot(td, r.y);
	td = zrot(td, r.z);
	return (td);
}

t_3d	unrot(t_3d td, t_rot r)
{
	td = zrot(td, -r.z);
	td = yrot(td, -r.y);
	td = xrot(td, -r.x);
	return (td);
}
