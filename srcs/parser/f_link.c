/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_link.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 14:13:40 by gperez            #+#    #+#             */
/*   Updated: 2018/10/15 16:29:03 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		link_grad(t_env *e)
{
	t_grad	*grads;
	t_obj	*objs;

	grads = e->s.grads;
	objs = e->s.objs;
	while (objs != NULL)
	{
		if (objs->id != 0)
		{
			while (grads != NULL && objs->id != grads->id)
				grads = grads->next;
			if (grads != NULL)
				objs->grad = grads;
		}
		objs = objs->next;
		grads = e->s.grads;
	}
}

static void	link_clips(t_env *e)
{
	t_obj	*objs;
	t_obj	*check;
	t_clip	*clips;

	objs = e->s.objs;
	while (objs != NULL)
	{
		check = e->s.objs;
		clips = objs->clips;
		while (clips != NULL)
		{
			check = e->s.objs;
			while ((check != NULL)
				&& (clips->id != check->id && -clips->id != check->id))
				check = check->next;
			if ((check != NULL)
				&& (clips->id == check->id || -clips->id == check->id))
					clips->obj = check;
			clips = clips->next;
		}
		objs = objs->next;
	}
}

void		link_obj(t_env *e)
{
	link_grad(e);
	link_clips(e);
}
