/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_check.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 13:51:39 by gperez            #+#    #+#             */
/*   Updated: 2018/11/12 15:56:15 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_pt(void *cam, char *l1, char *l2)
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

int		check_dir(void *cam, char *l1, char *l2)
{
	t_obj *obj;

	obj = (t_obj*)cam;
	if (!(ft_strcmp(l1, "dirx")))
	{
		obj->dir.x = ft_atod(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "diry")))
	{
		obj->dir.y = ft_atod(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "dirz")))
	{
		obj->dir.z = ft_atod(l2);
		return (0);
	}
	return (1);
}

int		check_rot(void *cam, char *l1, char *l2)
{
	t_obj *obj;

	obj = (t_obj*)cam;
	if (!(ft_strcmp(l1, "r")))
	{
		obj->r = ft_atod(l2);
		return (0);
	}
	return (1);
}

int		check_value(t_obj *obj, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "v")) || !(ft_strcmp(l1, "v1")))
	{
		obj->v[0] = ft_atod(l2);
		return (0);
	}
	else if (!(ft_strcmp(l1, "v2")))
	{
		obj->v[1] = ft_atod(l2);
		return (0);
	}
	else if (!(ft_strcmp(l1, "v3")))
	{
		obj->v[2] = ft_atod(l2);
		return (0);
	}
	else if (!(ft_strcmp(l1, "v4")))
	{
		obj->v[3] = ft_atod(l2);
		return (0);
	}
	return (1);
}
