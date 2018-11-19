/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moy_4_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 15:03:37 by kdouveno          #+#    #+#             */
/*   Updated: 2018/11/19 15:42:42 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo3d.h"

t_color	rgbmoy4(t_color c[4])
{
	t_color	out;
	t_rgb	*p;

	p = &out.p;
	p->a = ((int)c[0].p.a + (int)c[1].p.a + (int)c[2].p.a + (int)c[3].p.a) / 4;
	p->r = ((int)c[0].p.r + (int)c[1].p.r + (int)c[2].p.r + (int)c[3].p.r) / 4;
	p->g = ((int)c[0].p.g + (int)c[1].p.g + (int)c[2].p.g + (int)c[3].p.g) / 4;
	p->b = ((int)c[0].p.b + (int)c[1].p.b + (int)c[2].p.b + (int)c[3].p.b) / 4;
	return (out);
}
