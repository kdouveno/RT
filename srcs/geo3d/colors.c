/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:49:54 by kdouveno          #+#    #+#             */
/*   Updated: 2018/10/18 16:56:47 by kdouveno         ###   ########.fr       */
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
	out.p.a = 0;
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
	out.p.a = 0;
	return (out);
}

t_color	rgbneg(t_color c)
{
	return ((t_color){{255 - c.p.r, 255 - c.p.g, 255 - c.p.b, 0}});
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
	out.p.a = 0;
	return (out);
}
