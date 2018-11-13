/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_list_button.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:49:46 by schaaban          #+#    #+#             */
/*   Updated: 2018/11/13 17:43:01 by kdouveno         ###   ########.fr       */
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

	it = e->gui.actual_menu->list_btn;
	if (!it)
		return ;
	while (it)
	{
		it->aabb.y += (add) ? e->gui.actual_menu->cam_y :
			-e->gui.actual_menu->cam_y;
		it = it->next;
	}
}

static void			s_btn_update(t_env *e, t_list_btn *button)
{
	t_vec	mouse_v2;
	int		mpos_i[2];

	SDL_GetMouseState(&mpos_i[0], &mpos_i[1]);
	mouse_v2 = (t_vec){(double)mpos_i[0], (double)mpos_i[1], 0};
	if (aabb_col_pt(button->aabb, mouse_v2) && e->mouse_win)
	{
		button->st_hover = 1;
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
			button->st_pressing = 1;
		else
		{
			if (button->st_pressing)
			{
				button->st_pressing = 0;
				(button->action_call)(e);
			}
		}
	}
	else
	{
		button->st_pressing = 0;
		button->st_hover = 0;
	}
}

void				list_btn_update(t_env *e, t_list_btn *list, int mouse_out)
{
	t_list_btn	*it;

	it = list;
	while (it)
	{
		if (!mouse_out)
			s_btn_update(e, it);
		else
		{
			if (!(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)))
				it->st_pressing = 0;
			it->st_hover = 0;
		}
		it = it->next;
	}
}

void				list_btn_draw(t_list_win *win, t_list_btn *list)
{
	t_list_btn	*it;

	it = list;
	while (it)
	{
		SDL_BlitSurface(it->tex, NULL, win->render, &((SDL_Rect){it->aabb.x,
			it->aabb.y, it->aabb.w, it->aabb.h}));
		if (it->st_hover)
		{
			if (it->tex_hover)
				SDL_BlitSurface(it->tex_hover, NULL, win->render, &((SDL_Rect)
					{it->aabb.x, it->aabb.y, it->aabb.w, it->aabb.h}));
		}
		if (it->st_pressing)
		{
			if (it->tex_click)
				SDL_BlitSurface(it->tex_click, NULL, win->render, &((SDL_Rect)
					{it->aabb.x, it->aabb.y, it->aabb.w, it->aabb.h}));
		}
		it = it->next;
	}
}
