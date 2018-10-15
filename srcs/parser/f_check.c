/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_check.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 13:51:39 by gperez            #+#    #+#             */
/*   Updated: 2018/10/15 14:05:37 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_pt(void *cam, char* l1, char *l2)
{
	t_obj *obj;

	obj = (t_obj*)cam;
	if (!(ft_strcmp(l1, "tx")))
	{
		obj->t.x = ft_atod(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "ty")))
	{
		obj->t.y = ft_atod(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "tz")))
	{
		obj->t.z = ft_atod(l2);
		return (0);
	}
	return (1);
}

int		check_rot(void *cam, char* l1, char *l2)
{
	t_obj *obj;

	obj = (t_obj*)cam;
	if (!((ft_strcmp(l1, "dirx") && (ft_strcmp(l1, "rx")))))
	{
		obj->r.x = ft_atod(l2);
		return (0);
	}
	if (!((ft_strcmp(l1, "diry") && (ft_strcmp(l1, "ry")))))
	{
		obj->r.y = ft_atod(l2);
		return (0);
	}
	if (!((ft_strcmp(l1, "dirz") && (ft_strcmp(l1, "rz")))))
	{
		obj->r.z = ft_atod(l2);
		return (0);
	}
	return (1);
}
