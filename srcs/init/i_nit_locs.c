/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_nit_locs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 10:54:28 by kdouveno          #+#    #+#             */
/*   Updated: 2018/12/19 15:27:08 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline static void	link_locs_void(t_obj *begin, t_obj *o)
{
	while (begin)
	{
		if (begin->id >= 0 && begin->id == o->m.l.id && begin != o)
		{
			o->m.l.target = &(begin->m);
			return ;
		}
		begin = begin->next;
	}
}

void				link_locs(t_scene *s, void *o)
{
	link_locs_void((t_obj*)s->objs, o);
	link_locs_void((t_obj*)s->cams, o);
	link_locs_void((t_obj*)s->grads, o);
	link_locs_void((t_obj*)s->lits, o);
}
