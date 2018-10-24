/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_link_color_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:43:14 by gperez            #+#    #+#             */
/*   Updated: 2018/10/24 15:43:36 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		color_obj(t_obj *objs, t_grad *save_g)
{
	while (save_g)
	{
		if (save_g->id == objs->color.i)
		{
			if (save_g->b.c1 == 0)
				objs->color.i = save_g->color1.i;
			else
				objs->color.i = 0;
			return ;
		}
		save_g = save_g->next;
	}
	objs->color.i = 0;
}

void		link_color_obj(t_env *e)
{
	t_obj	*objs;
	int		check;

	check = 0;
	objs = e->s.objs;
	while (objs)
	{
		if (objs->b.c1 == 1)
			color_obj(objs, e->s.grads);
		objs = objs->next;
	}
}
