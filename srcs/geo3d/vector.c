/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 10:49:38 by kdouveno          #+#    #+#             */
/*   Updated: 2018/12/19 18:29:02 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo3d.h"

double	scalar_product(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	cross_product(t_vec a, t_vec b)
{
	return ((t_vec){a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x});
}

double	angle(t_vec a, t_vec b)
{
	return (acos(fabs((a.x * b.x + a.y * b.y + a.z * b.z)
			/ (sqrt(sq(a.x) + sq(a.y) + sq(a.z))
			* sqrt(sq(b.x) + sq(b.y) + sq(b.z))))));
}

t_rot	get_rot(t_vec a, double x)
{
	t_rot out;
	t_vec y;
	t_vec z;

	out = (t_rot){x, 0, 0};
	z = (t_vec){a.x, a.y, 0};
	if (a.x || a.y)
		out.z = (a.y < 0 ? -1 : 1) * (a.x < 0 ? M_PI - angle(z, (t_vec){1, 0, 0}) : angle(z, (t_vec){1, 0, 0}));
	a = zrot(a, -out.z);
	y = (t_vec){a.x, 0, a.z};
	if (a.x || a.z)
		out.y = (a.z > 0 ? -1 : 1) * angle(y, (t_vec){1, 0, 0});
	return (out);
}

double	get_norm(t_vec v)
{
	return (sqrt(sq(v.x) + sq(v.y) + sq(v.z)));
}
