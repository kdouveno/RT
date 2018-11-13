/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:19:24 by schaaban          #+#    #+#             */
/*   Updated: 2018/11/13 16:55:40 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline void	s_event_window(t_env *e)
{
	if (e->event.window.event == SDL_WINDOWEVENT_CLOSE)
	{
		if (e->event.window.windowID == e->id_main_win)
			e->exit = 1;
		else
			list_win_delone(&(e->list_win),
				list_win_get(e->list_win, e->event.window.windowID));
		e->mouse_win = NULL;
	}
	else if (e->event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
	{
		e->focus_win = list_win_get(e->list_win, e->event.window.windowID);
	}
	else if (e->event.window.event == SDL_WINDOWEVENT_ENTER)
		e->mouse_win = list_win_get(e->list_win, e->event.window.windowID);
	else if (e->event.window.event == SDL_WINDOWEVENT_LEAVE)
		e->mouse_win = NULL;
}

static inline void	s_event_keys(t_env *e)
{
	if (e->event.key.keysym.sym == SDLK_ESCAPE)
	{
		if (e->focus_win->id == e->id_main_win)
			e->exit = 1;
		else
			list_win_delone(&(e->list_win), e->focus_win);
		e->mouse_win = NULL;
	}
}

static inline void	s_event_wheel(t_env *e)
{
	if (e->event.wheel.y > 0)
	{
		e->gui.actual_menu->cam_y = ((e->gui.actual_menu->cam_y + 30) > 0) ?
			0 : e->gui.actual_menu->cam_y + 30;
	}
	else
	{
		if ((e->gui.actual_menu->cam_y - 30) <
			(UI_HEIGHT - e->gui.actual_menu->max_y - UI_BTN_Y))
		{
			if ((UI_HEIGHT - e->gui.actual_menu->max_y - UI_BTN_Y) <= 0)
				e->gui.actual_menu->cam_y =
					(UI_HEIGHT - e->gui.actual_menu->max_y - UI_BTN_Y);
		}
		else
			e->gui.actual_menu->cam_y -= 30;
	}
}

void				sdl_event_manager(t_env *e)
{
	while (SDL_PollEvent(&e->event))
	{
		if (e->event.type == SDL_KEYDOWN)
			s_event_keys(e);
		if (e->event.type == SDL_WINDOWEVENT)
			s_event_window(e);
		if (e->event.type == SDL_MOUSEWHEEL)
			s_event_wheel(e);
		if (e->event.type == SDL_QUIT)
			e->exit = 1;
	}
	return ;
}
