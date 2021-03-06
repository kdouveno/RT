/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_intercections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 16:36:07 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/18 15:39:58 by gperez           ###   ########.fr       */
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
	add_res(e, rlist, blank_reslist(o, res.a));
	if (res.type == TWORES)
		add_res(e, rlist, blank_reslist(o, res.b));
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
	add_res(e, rlist, blank_reslist(o, res.a));
	if (res.type == TWORES)
		add_res(e, rlist, blank_reslist(o, res.b));
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
	add_res(e, rlist, blank_reslist(o, res.a));
	if (res.type == TWORES)
		add_res(e, rlist, blank_reslist(o, res.b));
}

void	plane_line(t_env *e, t_line d, t_obj *o, t_reslist **rlist)
{
	if (!d.v.x)
		return ;
	add_res(e, rlist, blank_reslist(o, -d.m.x / d.v.x));
}

void	cuboid_line(t_env *e, t_line d, t_obj *o, t_reslist **rlist)
{
	double	d1;
	double	d2;
	double	d3;
	int		i;

	i = 0;
	while (i < 2)
	{
		d1 = ((i ? -1 : 1) * o->v[0] - d.m.x) / d.v.x;
		d2 = d.v.y * d1 + d.m.y;
		d3 = d.v.z * d1 + d.m.z;
		if (d1 > 0 && fabs(d2) < o->v[1] && fabs(d3) < o->v[2])
			add_res(e, rlist, blank_reslist(o, d1));
		d1 = ((i ? -1 : 1) * o->v[1] - d.m.y) / d.v.y;
		d2 = d.v.x * d1 + d.m.x;
		d3 = d.v.z * d1 + d.m.z;
		if (d1 > 0 && fabs(d2) < o->v[0] && fabs(d3) < o->v[2])
			add_res(e, rlist, blank_reslist(o, d1));
		d1 = ((i ? -1 : 1) * o->v[2] - d.m.z) / d.v.z;
		d2 = d.v.y * d1 + d.m.y;
		d3 = d.v.x * d1 + d.m.x;
		if (d1 > 0 && fabs(d2) < o->v[1] && fabs(d3) < o->v[0])
			add_res(e, rlist, blank_reslist(o, d1));
		i++;
	}
}
