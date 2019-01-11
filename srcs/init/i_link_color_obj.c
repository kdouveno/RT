/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_link_color_obj.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:43:14 by gperez            #+#    #+#             */
/*   Updated: 2019/01/11 14:57:53 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		color_obj(t_obj *objs, t_grad *save_g)
{
	while (save_g)
	{
		if (save_g->id == (signed)objs->mat.color.i)
		{
			if (save_g->b.c1 == 0)
				objs->mat.color.i = save_g->c1.i;
			else
				objs->mat.color.i = 0;
			objs->grad = save_g;
			return ;
		}
		save_g = save_g->next;
	}
	objs->mat.color.i = 0;
}

void			link_color_obj(t_env *e)
{
	t_obj	*objs;

	objs = e->s.objs;
	while (objs)
	{
		if (objs->b.c1 == 1)
			color_obj(objs, e->s.grads);
		objs = objs->next;
	}
}
