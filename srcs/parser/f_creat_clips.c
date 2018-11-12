/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_creat_clips.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:17:50 by gperez            #+#    #+#             */
/*   Updated: 2018/11/12 17:17:51 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rt.h"

void		creat_clips(t_env *e, t_obj *obj, char *l2)
{
	t_clip	*new;
	t_clip	*cp;

	cp = obj->clips;
	if (!(new = malloc(sizeof(t_clip))))
		error(e, MALLOC_ERROR);
	*new = (t_clip){atoi(l2), NULL, NULL};
	if (cp != NULL)
	{
		while (cp->next != NULL)
			cp = cp->next;
		cp->next = new;
	}
	else
		obj->clips = new;
}
