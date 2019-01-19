/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_creat_clips.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:17:50 by gperez            #+#    #+#             */
/*   Updated: 2019/01/11 15:16:46 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		creat_clips(t_env *e, t_obj *obj, char *l2)
{
	t_clip	*new;

	if (!(new = ft_memalloc(sizeof(t_clip))))
		error(e, MALLOC_ERROR);
	*new = (t_clip){ft_atoi(l2), NULL, obj->clips};
	obj->clips = new;
}
