/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 10:49:38 by kdouveno          #+#    #+#             */
/*   Updated: 2018/10/23 14:01:46 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo3d.h"
#include <stdio.h>

double	scalar_product(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
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

	y = (t_vec){a.x, 0, a.z};
	z = (t_vec){a.x, a.y, 0};
	out.x = x;
	out.y = angle(y, (t_vec){1, 0, 0});
	out.z = angle(z, (t_vec){1, 0, 0});
	return (out);
}
