/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 17:10:28 by gperez            #+#    #+#             */
/*   Updated: 2019/01/11 15:23:21 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		parse_color_obj(t_obj *obj, char *l2)
{
	obj->b.c1 = l2[0] == '#' ? 0 : 1;
	if (l2[0] == '#')
		obj->mat.color.i = (unsigned)atoi_hexa(&(l2[1]));
	else
		obj->mat.color.i = ft_atoi(l2);
}

static void		parse_color_grad(t_grad *grad, char *l2, int nb)
{
	if (nb == 1)
	{
		grad->b.c1 = l2[0] == '#' ? 0 : 1;
		if (l2[0] == '#')
			grad->c1.i = (unsigned)atoi_hexa(&l2[1]);
		else
			grad->c1.i = ft_atoi(l2);
	}
	else
	{
		grad->b.c2 = l2[0] == '#' ? 0 : 1;
		if (l2[0] == '#')
			grad->c2.i = (unsigned)atoi_hexa(&l2[1]);
		else
			grad->c2.i = ft_atoi(l2);
	}
}

void			parse_color(t_obj *obj, char *l2, t_grad *grad, int nb)
{
	if (grad == NULL && obj != NULL)
		parse_color_obj(obj, l2);
	if (obj == NULL && grad != NULL)
		parse_color_grad(grad, l2, nb);
}
