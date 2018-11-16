/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_link_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 14:13:40 by gperez            #+#    #+#             */
/*   Updated: 2018/11/15 17:16:40 by kdouveno         ###   ########.fr       */
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

static void	link_clip(t_env *e, t_obj* check, t_clip *clip, t_obj *obj)
{
	check->b.clip = 1;
	clip->obj = check;
	add_objlist(e, &check->clipping, obj);
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
					link_clip(e, check, clips, objs);
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
