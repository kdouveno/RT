/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_filter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 14:48:27 by gperez            #+#    #+#             */
/*   Updated: 2019/01/11 11:37:59 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	black(t_color p_color, int *c)
{
	t_color out;

	out.i = 0;
	*c += p_color.p.r;
	*c += p_color.p.g;
	*c += p_color.p.b;
	*c /= 3;
	out.p.r = *c;
	out.p.g = *c;
	out.p.b = *c;
	return (out);
}

t_color	sepia(t_color p_color, double c)
{
	c /= 255;
	p_color.p.r = c * 255;
	p_color.p.g = c * 209;
	p_color.p.b = c * 122;
	return (p_color);
}

t_color		filter(t_rendering *r, t_color p_color)
{
	t_color	out;
	int		c;

	c = 0;
	if (r->c->data.filter == 'b' || r->c->data.filter == 's')
	{
		out.i = 0;
		out = black(p_color, &c);
		if (r->c->data.filter == 's')
			out = sepia(out, (double)c);
		return (out);
	}
	return (p_color);
}
