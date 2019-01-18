/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_nit_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:58:04 by gperez            #+#    #+#             */
/*   Updated: 2019/01/18 16:58:16 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	check_link_loop(t_env *e, t_matrix *o, t_matrix *obj)
{
	if (!obj)
		return ;
	if (o == obj)
		error(e, LINK_CIRCLE_ERROR);
	else
	{
		check_link_loop(e, o, obj->l.target);
	}
}

void	check_clip_loop(t_env *e, t_obj *o, t_obj *original, int i)
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
