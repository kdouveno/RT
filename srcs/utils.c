/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:14:53 by kdouveno          #+#    #+#             */
/*   Updated: 2018/12/11 16:19:44 by kdouveno         ###   ########.fr       */
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
	return (i);
}
