/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 14:21:48 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/20 18:03:50 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_color	cast_light(t_rendering *r, t_lit *l, t_reslist *res,
	t_line line)
{
	t_reslist	rl;
	t_color		tmp;
	rl = intersec(r, line);
	if (rl.t > 1.0 - PRE || get_norm(line.v) < PRE)
		return (l->color);
	else if (rl.o && rl.o->mat.tr > 0)
	{
		tmp = cast_light(r, l, res, get_line(rl.pt, res->pt));
		return (tmp.p.a == 1 ? tmp
			: rgbpro(rgbmin(tmp, rgbneg(rgbmid(get_pt_color(*rl.o, rl.pt,
				NULL), (t_color)0xffffffU, rl.o->mat.tr))), rl.o->mat.tr));
	}
	else
		return (t_color){{0, 0, 0, 1}};
}

t_color			catch_light(t_rendering *r, t_lit *l, t_reslist *res)
{
	return (cast_light(r, l, res, get_line(l->cpt, res->pt)));
}
