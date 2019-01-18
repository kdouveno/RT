/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:23:43 by gperez            #+#    #+#             */
/*   Updated: 2019/01/18 16:28:44 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	free_clip(t_clip *clip)
{
	t_clip	*next;

	while (clip != NULL)
	{
		next = clip->next;
		ft_memdel((void**)&clip);
		clip = next;
	}
}

static void	free_clipin(t_objlist *clipin)
{
	t_objlist	*next;

	while (clipin != NULL)
	{
		next = clipin->next;
		ft_memdel((void**)&clipin);
		clipin = next;
	}
}

void		free_obj(t_obj *obj)
{
	t_obj	*next;

	while (obj != NULL)
	{
		next = obj->next;
		free_clip(obj->clips);
		free_clipin(obj->clipping);
		(obj->mat.txt) ? SDL_FreeSurface(obj->mat.txt) : 0;
		(obj->mat.txt_bm) ? SDL_FreeSurface(obj->mat.txt_bm) : 0;
		ft_memdel((void**)&obj);
		obj = next;
	}
}
