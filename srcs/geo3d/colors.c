/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:49:54 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/10 14:14:18 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo3d.h"

t_color	rgbpro(t_color c, double m)
{
	t_color		out;
	double		test;

	if ((test = (double)c.p.r * m) > 255)
		test = 255;
	if (test < 0)
		test = 0;
	out.p.r = (int)test;
	if ((test = (double)c.p.g * m) > 255)
		test = 255;
	if (test < 0)
		test = 0;
	out.p.g = (int)test;
	if ((test = (double)c.p.b * m) > 255)
		test = 255;
	if (test < 0)
		test = 0;
	out.p.b = (int)test;
	return (out);
}

t_color	rgbadd(t_color c1, t_color c2)
{
	t_color	out;
	int		test;

	if ((test = (int)c1.p.r + c2.p.r) > 255)
		test = 255;
	out.p.r = test;
	if ((test = (int)c1.p.g + c2.p.g) > 255)
		test = 255;
	out.p.g = test;
	if ((test = (int)c1.p.b + c2.p.b) > 255)
		test = 255;
	out.p.b = test;
	return (out);
}

t_color	rgbneg(t_color c)
{
	t_color out;

	out.p.r = 255 - c.p.r;
	out.p.g = 255 - c.p.g;
	out.p.b = 255 - c.p.b;
	out.p.a = c.p.a;
	return (out);
}

t_color	rgbmin(t_color c1, t_color c2)
{
	t_color	out;
	int		test;

	if ((test = (int)c1.p.r - c2.p.r) < 0)
		test = 0;
	out.p.r = test;
	if ((test = (int)c1.p.g - c2.p.g) < 0)
		test = 0;
	out.p.g = test;
	if ((test = (int)c1.p.b - c2.p.b) < 0)
		test = 0;
	out.p.b = test;
	return (out);
}

t_color	rgbmid(t_color c1, t_color c2, float mid)
{
	int a;
	int r;
	int g;
	int b;

	a = (signed)c1.p.a + ((signed)c2.p.a - c1.p.a) * mid;
	r = (signed)c1.p.r + ((signed)c2.p.r - c1.p.r) * mid;
	g = (signed)c1.p.g + ((signed)c2.p.g - c1.p.g) * mid;
	b = (signed)c1.p.b + ((signed)c2.p.b - c1.p.b) * mid;
	return ((t_color){{b, g, r, a}});
}

double rgb_litlevel(t_color c)
{
	return ((double)((c.p.r + c.p.g + c.p.b) / 3) / 255);
}
