/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_check.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 13:51:39 by gperez            #+#    #+#             */
/*   Updated: 2018/12/21 17:38:24 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_loc(t_env *e, void *obj, char *l1, char *l2)
{
	t_obj *o;

	o = (t_obj*)obj;
	if (!ft_strcmp(l1, "pos"))
		return (parse_3d(e, &o->m.pt, l2));
	else if (!ft_strcmp(l1, "t"))
		return (parse_3d(e, &o->m.t, l2));
	else if (!ft_strcmp(l1, "link"))
		o->m.l.id = ft_atoi(l2);
	else if (!ft_strcmp(l1, "rot"))
		return (parse_3d(e, &o->m.rot, l2));
	else
		return (1);
	return (0);
}

int		check_pt(void *cam, char *l1, char *l2)
{
	t_obj *obj;

	obj = (t_obj*)cam;
	if (!(ft_strcmp(l1, "tx")))
		obj->m.t.x = ft_atod(l2);
	else if (!(ft_strcmp(l1, "ty")))
		obj->m.t.y = ft_atod(l2);
	else if (!(ft_strcmp(l1, "tz")))
		obj->m.t.z = ft_atod(l2);
	else
		return (1);
	return (0);
}

int		check_dir(void *cam, char *l1, char *l2)
{
	t_obj *obj;

	obj = (t_obj*)cam;
	if (!(ft_strcmp(l1, "rotx")))
		obj->m.rot.x = ft_atod(l2);
	else if (!(ft_strcmp(l1, "roty")))
		obj->m.rot.y = ft_atod(l2);
	else if (!(ft_strcmp(l1, "rotz")))
		obj->m.rot.z = ft_atod(l2);
	else
		return (1);
	return (0);
}

int		check_rot(void *cam, char *l1, char *l2)
{
	t_obj *obj;

	obj = (t_obj*)cam;
	if (!(ft_strcmp(l1, "r")))
	{
		obj->m.r = ft_atod(l2);
		return (0);
	}
	return (1);
}

int		check_value(t_obj *obj, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "v")) || !(ft_strcmp(l1, "v1")))
		obj->v[0] = ft_atod(l2);
	else if (!(ft_strcmp(l1, "v2")))
		obj->v[1] = ft_atod(l2);
	else if (!(ft_strcmp(l1, "v3")))
		obj->v[2] = ft_atod(l2);
	else if (!(ft_strcmp(l1, "v4")))
		obj->v[3] = ft_atod(l2);
	else
		return (1);
	return (0);
}
