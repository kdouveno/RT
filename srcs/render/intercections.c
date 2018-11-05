/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intercections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 16:36:07 by kdouveno          #+#    #+#             */
/*   Updated: 2018/11/04 15:21:14 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_polyres	solve_polynome(double a, double b, double c)
{
	t_polyres	out;
	double		delta;

	out.type = NORES;
	if (a != 0)
	{
		a *= 2;
		delta = b * b - 2 * a * c;
		if (delta > 0)
		{
			delta = sqrt(delta);
			out.type = TWORES;
			out.a = (-b - delta) / a;
			out.b = (-b + delta) / a;
		}
		else if (!delta)
		{
			out.type = ONERES;
			out.a = -b / a;
		}
	}
	return (out);
}

double		cone_line(t_line d, double a)
{
	double		out;
	t_polyres	res;
	double		ta;

	ta = sq(tan(a));
	res = solve_polynome(
		sq(d.v.x) + sq(d.v.y) - sq(d.v.z) * ta,
		2 * (d.v.x * d.m.x + d.v.y * d.m.y - d.v.z * d.m.z * ta),
		sq(d.m.x) + sq(d.m.y) - sq(d.m.z) * ta);
	if (res.type == NORES)
		return (-1);
	out = res.a;
	if (res.type == TWORES && (res.b < res.a || res.a < 0) && res.b >= 0)
		out = res.b;
	return (out);
}

double		cylinder_line(t_line d, double r)
{
	double		out;
	t_polyres	res;

	res = solve_polynome(
		sq(d.v.x) + sq(d.v.y),
		2 * (d.v.x * d.m.x + d.v.y * d.m.y),
		sq(d.m.x) + sq(d.m.y) - r * r);
	if (res.type == NORES)
		return (-1);
	out = res.a;
	if (res.type == TWORES && (res.b < res.a || res.a < 0) && res.b >= 0)
		out = res.b;
	return (out);
}

double		sphere_line(t_line d, double r)
{
	double		out;
	t_polyres	res;

	res = solve_polynome(
		sq(d.v.x) + sq(d.v.y) + sq(d.v.z),
		2 * (d.v.x * d.m.x + d.v.y * d.m.y + d.v.z * d.m.z),
		sq(d.m.x) + sq(d.m.y) + sq(d.m.z) - r * r);
	if (res.type == NORES)
		return (-1);
	out = res.a;
	if (res.type == TWORES && (res.b < res.a || res.a < 0) && res.b >= 0)
		out = res.b;
	return (out);
}

double		plane_line(t_line d, double empty)
{
	(void)empty;
	if (!d.v.x)
		return (-1);
	return (-d.m.x / d.v.x);
}
