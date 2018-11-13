/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 17:27:29 by schaaban          #+#    #+#             */
/*   Updated: 2018/11/13 15:46:59 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				list_win_add(t_env *e, t_list_win **list, t_list_win new)
{
	t_list_win	*dnew;

	if (!list)
		return ;
	if (new.win)
	{
		if (!(new.render = SDL_GetWindowSurface(new.win)))
		{
			SDL_DestroyWindow(new.win);
			error(e, MALLOC_ERROR);
		}
	}
	else
		error(e, MALLOC_ERROR);
	if (!(dnew = (t_list_win*)ft_memalloc(sizeof(t_list_win))))
	{
		SDL_DestroyWindow(new.win);
		error(e, MALLOC_ERROR);
	}
	new.id = SDL_GetWindowID(new.win);
	new.next = *list;
	*dnew = new;
	*list = dnew;
}

void				list_win_del(t_list_win *list)
{
	t_list_win	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->win)
			SDL_DestroyWindow(tmp->win);
		ft_memdel((void**)&tmp);
	}
}

void				list_win_delone(t_list_win **list, t_list_win *el)
{
	t_list_win	*last;
	t_list_win	*actual;

	if (!list)
		return ;
	actual = *list;
	last = NULL;
	while (actual && actual != el)
	{
		last = actual;
		actual = actual->next;
	}
	if (!actual)
		return ;
	if (last)
		last->next = actual->next;
	else
		*list = actual->next;
	if (actual->win)
		SDL_DestroyWindow(actual->win);
	ft_memdel((void**)&actual);
}

t_list_win			*list_win_get(t_list_win *list, Uint32 id)
{
	t_list_win	*it;

	it = list;
	while (it)
	{
		if (it->id == id)
			return (it);
		it = it->next;
	}
	return (NULL);
}
