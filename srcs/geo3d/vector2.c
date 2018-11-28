/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 15:46:33 by kdouveno          #+#    #+#             */
/*   Updated: 2018/10/01 15:50:40 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo3d.h"

t_vec	vecpro(t_vec v, double a)
{
	return ((t_vec){v.x * a, v.y * a, v.z * a});
}

t_pt	apply(t_vec v, t_pt p)
{
	return ((t_pt){p.x + v.x, p.y + v.y, p.z + v.z});
}

t_vec	normalise(t_vec in)
{
	t_vec	out;
	double	t;

	t = sqrt(1 / (sq(in.x) + sq(in.y) + sq(in.z)));
	out.x = in.x * t;
	out.y = in.y * t;
	out.z = in.z * t;
	return (out);
}

t_vec	get_vector(t_pt a, t_pt b)
{
	return ((t_vec){b.x - a.x, b.y - a.y, b.z - a.z});
}

t_vec	vec_rev(t_vec v)
{
	return ((t_vec){-v.x, -v.y, -v.z});
}
