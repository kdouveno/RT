/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:19:24 by schaaban          #+#    #+#             */
/*   Updated: 2018/12/11 14:36:22 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			s_event_window(t_env *e)
{
	if (e->ui.event.window.event == SDL_WINDOWEVENT_CLOSE)
	{
		if (e->ui.event.window.windowID == e->ui.id_main_win)
			e->ui.exit = 1;
		else
			list_win_delone(&(e->ui.list_win),
				list_win_get(e->ui.list_win, e->ui.event.window.windowID));
		e->ui.focus_win = list_win_get(e->ui.list_win, e->ui.id_main_win);
		e->ui.mouse_win = list_win_get(e->ui.list_win, e->ui.id_main_win);
	}
	else if (e->ui.event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
		e->ui.focus_win = list_win_get(e->ui.list_win, e->ui.event.window.windowID);
	else if (e->ui.event.window.event == SDL_WINDOWEVENT_ENTER)
		e->ui.mouse_win = list_win_get(e->ui.list_win, e->ui.event.window.windowID);
	else if (e->ui.event.window.event == SDL_WINDOWEVENT_LEAVE)
		e->ui.mouse_win = NULL;
}

static void			s_event_keys(t_env *e)
{
	if (e->ui.event.key.keysym.sym == SDLK_ESCAPE)
	{
		if (e->ui.focus_win->id == e->ui.id_main_win)
			e->ui.exit = 1;
		else
			list_win_delone(&(e->ui.list_win), e->ui.focus_win);
		e->ui.focus_win = NULL;
		e->ui.mouse_win = list_win_get(e->ui.list_win, e->ui.id_main_win);
	}
}

static void			s_event_wheel(t_env *e)
{
	if (e->ui.mouse_win->id != e->ui.id_main_win)
		return ;
	if (e->ui.event.wheel.y > 0)
	{
		e->ui.gui.actual_menu->cam_y = ((e->ui.gui.actual_menu->cam_y
			+ UI_SCROLL_SP) > 0) ?
			0 : e->ui.gui.actual_menu->cam_y + UI_SCROLL_SP;
	}
	else
	{
		if ((e->ui.gui.actual_menu->cam_y - UI_SCROLL_SP) <
			(UI_HEIGHT - e->ui.gui.actual_menu->max_y - UI_BTN_Y))
		{
			if ((UI_HEIGHT - e->ui.gui.actual_menu->max_y - UI_BTN_Y) <= 0)
				e->ui.gui.actual_menu->cam_y =
					(UI_HEIGHT - e->ui.gui.actual_menu->max_y - UI_BTN_Y);
		}
		else
			e->ui.gui.actual_menu->cam_y -= UI_SCROLL_SP;
	}
}

void				sdl_event_manager(t_env *e)
{
	while (SDL_PollEvent(&e->ui.event))
	{
		if (e->ui.event.type == SDL_KEYDOWN)
			s_event_keys(e);
		if (e->ui.event.type == SDL_WINDOWEVENT)
			s_event_window(e);
		if (e->ui.event.type == SDL_MOUSEWHEEL)
			s_event_wheel(e);
		if (e->ui.event.type == SDL_QUIT)
			e->ui.exit = 1;
	}
	return ;
}
