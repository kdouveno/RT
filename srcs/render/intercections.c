/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intercections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 16:36:07 by kdouveno          #+#    #+#             */
/*   Updated: 2018/11/07 19:44:11 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cone_line(t_env *e, t_line d, t_obj *o, t_reslist **rlist)
{
	t_polyres	res;
	double		ta;

	ta = sq(tan(o->v[0]));
	res = solve_polynome(
		sq(d.v.x) + sq(d.v.y) - sq(d.v.z) * ta,
		2 * (d.v.x * d.m.x + d.v.y * d.m.y - d.v.z * d.m.z * ta),
		sq(d.m.x) + sq(d.m.y) - sq(d.m.z) * ta);
	if (res.type == NORES)
		return ;
	add_res(e, rlist, (t_reslist){res.a, o, NULL});
	if (res.type == TWORES)
		add_res(e, rlist, (t_reslist){res.b, o, NULL});
}

void	cylinder_line(t_env *e, t_line d, t_obj *o, t_reslist **rlist)
{
	t_polyres	res;

	res = solve_polynome(
		sq(d.v.x) + sq(d.v.y),
		2 * (d.v.x * d.m.x + d.v.y * d.m.y),
		sq(d.m.x) + sq(d.m.y) - o->v[0] * o->v[0]);
	if (res.type == NORES)
		return ;
	add_res(e, rlist, (t_reslist){res.a, o, NULL});
	if (res.type == TWORES)
		add_res(e, rlist, (t_reslist){res.b, o, NULL});
}

void	sphere_line(t_env *e, t_line d, t_obj *o, t_reslist **rlist)
{
	t_polyres	res;

	res = solve_polynome(
		sq(d.v.x) + sq(d.v.y) + sq(d.v.z),
		2 * (d.v.x * d.m.x + d.v.y * d.m.y + d.v.z * d.m.z),
		sq(d.m.x) + sq(d.m.y) + sq(d.m.z) - o->v[0] * o->v[0]);
	if (res.type == NORES)
		return ;
	add_res(e, rlist, (t_reslist){res.a, o, NULL});
	if (res.type == TWORES)
		add_res(e, rlist, (t_reslist){res.b, o, NULL});
}

void	plane_line(t_env *e, t_line d, t_obj *o, t_reslist **rlist)
{
	if (!d.v.x)
		return ;
	add_res(e, rlist, (t_reslist){-d.m.x / d.v.x, o, NULL});
}
