/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_button_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:49:46 by schaaban          #+#    #+#             */
/*   Updated: 2018/12/18 19:16:44 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				list_btn_add(t_env *e, t_list_btn **list, t_list_btn new)
{
	t_list_btn	*dnew;

	if (!list)
		return ;
	if (!new.tex)
		error(e, MALLOC_ERROR);
	if (!(dnew = (t_list_btn*)ft_memalloc(sizeof(t_list_btn))))
	{
		SDL_FreeSurface(new.tex);
		error(e, MALLOC_ERROR);
	}
	new.st_hover = 0;
	new.st_pressing = 0;
	new.aabb.w = new.tex->w;
	new.aabb.h = new.tex->h;
	new.next = *list;
	*dnew = new;
	*list = dnew;
}

void				list_btn_del(t_list_btn *list)
{
	t_list_btn	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->tex)
			SDL_FreeSurface(tmp->tex);
		if (tmp->tex_hover)
			SDL_FreeSurface(tmp->tex_hover);
		if (tmp->tex_click)
			SDL_FreeSurface(tmp->tex_click);
		ft_memdel((void**)&tmp);
	}
}

void				list_btn_cam(t_env *e, int add)
{
	t_list_btn	*it;

	it = e->ui.gui.actual_menu->list_btn;
	if (!it)
		return ;
	while (it)
	{
		it->aabb.y += (add) ? e->ui.gui.actual_menu->cam_y :
			-e->ui.gui.actual_menu->cam_y;
		it = it->next;
	}
}
