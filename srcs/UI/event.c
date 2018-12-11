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

#include "rtui.h"

static void			s_event_window(t_rt *rt)
{
	if (rt->event.window.event == SDL_WINDOWEVENT_CLOSE)
	{
		if (rt->event.window.windowID == rt->id_main_win)
			rt->exit = 1;
		else
			list_win_delone(&(rt->list_win),
				list_win_get(rt->list_win, rt->event.window.windowID));
		rt->focus_win = list_win_get(rt->list_win, rt->id_main_win);
		rt->mouse_win = list_win_get(rt->list_win, rt->id_main_win);
	}
	else if (rt->event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
		rt->focus_win = list_win_get(rt->list_win, rt->event.window.windowID);
	else if (rt->event.window.event == SDL_WINDOWEVENT_ENTER)
		rt->mouse_win = list_win_get(rt->list_win, rt->event.window.windowID);
	else if (rt->event.window.event == SDL_WINDOWEVENT_LEAVE)
		rt->mouse_win = NULL;
}

static void			s_event_keys(t_rt *rt)
{
	if (rt->event.key.keysym.sym == SDLK_ESCAPE)
	{
		if (rt->focus_win->id == rt->id_main_win)
			rt->exit = 1;
		else
			list_win_delone(&(rt->list_win), rt->focus_win);
		rt->focus_win = NULL;
		rt->mouse_win = list_win_get(rt->list_win, rt->id_main_win);
	}
}

static void			s_event_wheel(t_rt *rt)
{
	if (rt->mouse_win->id != rt->id_main_win)
		return ;
	if (rt->event.wheel.y > 0)
	{
		rt->gui.actual_menu->cam_y = ((rt->gui.actual_menu->cam_y
			+ UI_SCROLL_SP) > 0) ?
			0 : rt->gui.actual_menu->cam_y + UI_SCROLL_SP;
	}
	else
	{
		if ((rt->gui.actual_menu->cam_y - UI_SCROLL_SP) <
			(UI_HEIGHT - rt->gui.actual_menu->max_y - UI_BTN_Y))
		{
			if ((UI_HEIGHT - rt->gui.actual_menu->max_y - UI_BTN_Y) <= 0)
				rt->gui.actual_menu->cam_y =
					(UI_HEIGHT - rt->gui.actual_menu->max_y - UI_BTN_Y);
		}
		else
			rt->gui.actual_menu->cam_y -= UI_SCROLL_SP;
	}
}

void				sdl_event_manager(t_rt *rt)
{
	while (SDL_PollEvent(&rt->event))
	{
		if (rt->event.type == SDL_KEYDOWN)
			s_event_keys(rt);
		if (rt->event.type == SDL_WINDOWEVENT)
			s_event_window(rt);
		if (rt->event.type == SDL_MOUSEWHEEL)
			s_event_wheel(rt);
		if (rt->event.type == SDL_QUIT)
			rt->exit = 1;
	}
	return ;
}
