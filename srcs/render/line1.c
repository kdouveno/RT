/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 12:59:31 by kdouveno          #+#    #+#             */
/*   Updated: 2018/11/06 16:42:15 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cone_line(t_env *e, t_line d, t_obj *o, t_insecres **res)
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
		return ;
	add_res(e, res, (t_reslist){res.a, o, NULL});
	if (res.type == TWORES)
		add_res(e, res, (t_reslist){res.b, o, NULL});
	return (out);
}

void	cylinder_line(t_env *e, t_line d, t_obj *o, t_insecres **res)
{
	double		out;
	t_polyres	res;

	res = solve_polynome(
		sq(d.v.x) + sq(d.v.y),
		2 * (d.v.x * d.m.x + d.v.y * d.m.y),
		sq(d.m.x) + sq(d.m.y) - r * r);
	if (res.type == NORES)
		return ;
	add_res(e, res, (t_reslist){res.a, o, NULL});
	if (res.type == TWORES)
		add_res(e, res, (t_reslist){res.b, o, NULL});
	return (out);
}

void	sphere_line(t_env *e, t_line d, t_obj *o, t_insecres **res)
{
	double		out;
	t_polyres	res;

	res = solve_polynome(
		sq(d.v.x) + sq(d.v.y) + sq(d.v.z),
		2 * (d.v.x * d.m.x + d.v.y * d.m.y + d.v.z * d.m.z),
		sq(d.m.x) + sq(d.m.y) + sq(d.m.z) - r * r);
	if (res.type == NORES)
		return ;
	add_res(e, res, (t_reslist){res.a, o, NULL});
	if (res.type == TWORES)
		add_res(e, res, (t_reslist){res.b, o, NULL});
	return (out);
}

void	plane_line(t_env *e, t_line d, t_obj *o, t_insecres **res)
{
	if (!d.v.x)
		return ;
	return (-d.m.x / d.v.x);
}
