/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 14:36:38 by kdouveno          #+#    #+#             */
/*   Updated: 2018/11/04 16:42:13 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	get_vector(t_pt a, t_pt b)
{
	return ((t_vec){b.x - a.x, b.y - a.y, b.z - a.z});
}

t_line	get_line(t_pt a, t_pt b)
{
	return ((t_line){a, get_vector(a, b)});
}

t_pt	get_linept(t_line d, double t)
{
	t_pt out;

	out = (t_pt){d.v.x * t + d.m.x, d.v.y * t + d.m.y, d.v.z * t + d.m.z};
	return (out);
}
