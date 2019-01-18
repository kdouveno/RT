/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_nit_grad_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:56:51 by gperez            #+#    #+#             */
/*   Updated: 2019/01/18 16:57:53 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_grad(t_env *e, t_scene *s)
{
	t_grad	*grads;

	grads = s->grads;
	while (grads)
	{
		link_locs(s, grads);
		check_link_loop(e, &grads->m, grads->m.l.target);
		grads->cpt = trans_pt((t_pt){0, 0, 0}, &grads->m);
		grads->r = trans_vec(get_vector(grads->m.pt, grads->r), &grads->m);
		grads = grads->next;
	}
}

void		init_objs(t_env *e, t_scene *s)
{
	t_obj	*objs;

	objs = s->objs;
	while (objs)
	{
		check_clip_loop(e, objs, objs, 0);
		link_locs(s, objs);
		check_link_loop(e, &objs->m, objs->m.l.target);
		if (objs->m.r >= 0)
			objs->m.rot = get_rot(objs->m.rot, objs->m.r);
		else
			objs->m.rot = (t_3d){rad(objs->m.rot.x),
			rad(objs->m.rot.y), rad(objs->m.rot.z)};
		if (objs->type == CONE)
			objs->v[0] = rad(objs->v[0]);
		objs = objs->next;
	}
}
