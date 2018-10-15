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

void static		link_lst_clips(t_env *e)
{
	t_clip	*save;

	(void)save;
	(void)e;
}

void			link_obj(t_env *e)
{
	link_grad(e);
	link_lst_clips(e);
}
