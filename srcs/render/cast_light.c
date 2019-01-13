/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 14:21:48 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/13 18:34:19 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		cast_light(t_rendering *r, t_lit *l, t_reslist *res, t_line line)
{
	t_reslist	rl;
	t_color		tmp;

	// printf("\t%f %f %f\n", line.m.x, line.m.y, line.m.z);
	rl = intersec(r, line);
	if (rl.t > 1 - PRE)
	{
		return (l->color);
	}
	else if (rl.o && rl.o->mat.tr > 0)
	{
		tmp = cast_light(r, l, res, get_line(rl.pt, res->pt));
		return (tmp.p.a == 1 ? tmp
			: rgbmid(rgbpro(get_pt_color(*rl.o, rl.pt, NULL), rl.o->mat.tr), tmp, rl.o->mat.tr));
	}
	else
		return (t_color){{0, 0, 0, 1}};
}

t_color		catch_light(t_rendering *r, t_lit *l, t_reslist *res)
{
	// printf("%f %f %f | %f %f %f\n", l->cpt.x, l->cpt.y, l->cpt.z, res->pt.x, res->pt.y, res->pt.z);
	return (cast_light(r, l, res, get_line(l->cpt, res->pt)));
}
