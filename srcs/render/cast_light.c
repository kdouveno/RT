/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 14:21:48 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/13 15:09:38 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color		cast_light(t_rendering *r, t_lit *l, t_reslist *res, t_line line)
{
	t_reslist	rl;
	t_color		tmp;

	rl = intersec(r, line);
	if (rl.t > 1 - PRE)
		return (rgbpro(l->color, l->power));
	else if (rl.o->mat.tr > 0)
	{
		tmp = cast_light(r, l, res, get_line(rl.pt, res->pt));
		return (tmp.p.a == 1 ? tmp
			: rgbmid(rl.o->mat.color, tmp, rl.o->mat.tr));
	}
	else
		return (t_color){{0, 0, 0, 1}};
}

t_color		catch_light(t_rendering *r, t_lit *l, t_reslist *res)
{
	return (cast_light(r, l, res, get_line(l->cpt, res->pt)));
}
