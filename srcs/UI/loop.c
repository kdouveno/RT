/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:15:01 by schaaban          #+#    #+#             */
/*   Updated: 2018/12/10 16:29:00 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				sdl_loop(t_env *e)
{
	t_list_win	*it_list_win;

	while (!e->ui.exit)
	{
		sdl_event_manager(rt);
		ft_update(rt);
		ft_clear_screen(0xff000000,
			list_win_get(e->ui.list_win, e->ui.id_main_win));
		list_btn_draw(rt, list_win_get(e->ui.list_win, e->ui.id_main_win),
			e->ui.gui.actual_menu->list_btn);
		list_btn_cam(rt, 0);
		it_list_win = e->ui.list_win;
		while (it_list_win)
		{
			SDL_UpdateWindowSurface(it_list_win->win);
			it_list_win = it_list_win->next;
		}
	}
	rt_exit(rt);
}
