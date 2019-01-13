/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:14:53 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/11 14:20:54 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	count_cams(t_env *e)
{
	t_cam	*begin;
	int		i;

	begin = e->s.cams;
	i = 0;
	while (begin)
	{
		begin = begin->next;
		i++;
	}
	if (i > 99)
		i = 99;
	return (i);
}
