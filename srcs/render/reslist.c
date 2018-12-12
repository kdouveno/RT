/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reslist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:56:58 by kdouveno          #+#    #+#             */
/*   Updated: 2018/12/12 14:26:47 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_res(t_env *e, t_reslist **cur, t_reslist t)
{
	t_reslist	*last;
	t_reslist	*tmp;

	if (t.t < PRE)
		return ;
	tmp = *cur;
	last = NULL;
	while (tmp && t.t > tmp->t)
	{
		last = tmp;
		tmp = tmp->next;
	}
	t.next = tmp;
	if (!(tmp = (t_reslist*)malloc(sizeof(t_reslist))))
		error(e, MALLOC_ERROR);
	*tmp = t;
	last ? (last->next = tmp) : (*cur = tmp);
}

void	free_res(t_reslist *list)
{
	t_reslist	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}
