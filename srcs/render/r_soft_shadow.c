/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_soft_shadow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:53:05 by gperez            #+#    #+#             */
/*   Updated: 2019/01/18 16:55:18 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color			soft_shadow2(t_rendering *r, t_reslist *res, t_lit l, int rec)
{
	t_pt		pts[6];
	t_color		out;
	int			i;

	i = 0;
	out.i = 0;
	pts[0] = (t_pt){l.cpt.x + l.radius, l.cpt.y, l.cpt.z};
	pts[1] = (t_pt){l.cpt.x - l.radius, l.cpt.y, l.cpt.z};
	pts[2] = (t_pt){l.cpt.x, l.cpt.y + l.radius, l.cpt.z};
	pts[3] = (t_pt){l.cpt.x, l.cpt.y - l.radius, l.cpt.z};
	pts[4] = (t_pt){l.cpt.x, l.cpt.y, l.cpt.z + l.radius};
	pts[5] = (t_pt){l.cpt.x, l.cpt.y, l.cpt.z - l.radius};
	while (((i++) || 1) && (i < 6) | (int)(l.cpt = pts[i]).x)
		out = rgbadd(out, rgbpro(soft_shadow(r, res, l, rec + 1), SHADOW_C));
	return (out);
}
