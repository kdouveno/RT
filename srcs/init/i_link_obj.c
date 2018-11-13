/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_link_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 14:13:40 by gperez            #+#    #+#             */
/*   Updated: 2018/11/12 17:18:32 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_objlist(t_env *e, t_objlist **list, t_obj *ajout)
{
	t_objlist	*add;

	if (!(add = (t_objlist*)malloc(sizeof(t_objlist))))
		error(e, MALLOC_ERROR);
	*add = (t_objlist){ajout, *list};
	*list = add;
}

void	link_clips(t_env *e)
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
				{
					check->b.clip = 1;
					clips->obj = check;
					add_objlist(e, &check->clipping, objs);
				}
			clips = clips->next;
		}
		objs = objs->next;
	}
}

void		link_obj(t_env *e)
{
	link_color_grad(e);
	link_color_obj(e);
	link_clips(e);
}