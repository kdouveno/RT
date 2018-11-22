/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:53:22 by kdouveno          #+#    #+#             */
/*   Updated: 2018/11/22 10:47:22 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void check_clip_loop(t_env *e, t_obj *o, t_obj *original, int i)
{
	t_objlist	*clpin;

	if (i && o == original)
		error(e, CLIP_CIRCLE_ERROR);
	i = 1;
	clpin = o->clipping;
	while (clpin)
	{
		check_clip_loop(e, clpin->obj, original, i);
		clpin = clpin->next;
	}
}

void 		init_objs(t_env *e, t_scene *s)
{
	t_obj	*objs;

	objs = s->objs;
	while (objs)
	{
		if (objs->r >= 0)
			objs->dir = get_rot(objs->dir, objs->r);
		else
			objs->dir = (t_three_d){rad(objs->dir.x),
			rad(objs->dir.y), rad(objs->dir.z)};
		if (objs->type == CONE)
			objs->v[0] = rad(objs->v[0]);
		check_clip_loop(e, objs, objs, 0);
		objs = objs->next;
	}
}
