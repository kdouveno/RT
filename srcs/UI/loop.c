/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:15:01 by schaaban          #+#    #+#             */
/*   Updated: 2019/01/15 15:01:42 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				sdl_loop(t_env *e)
{
	t_list_win	*it_list_win;

	while (42)
	{
		sdl_event_manager(e);
		ft_update(e);
		ft_clear_screen(0xff000000,
			list_win_get(e->ui.list_win, e->ui.id_main_win));
		list_btn_draw(e, list_win_get(e->ui.list_win, e->ui.id_main_win),
			e->ui.gui.actual_menu->list_btn);
		list_btn_cam(e, 0);
		pbar_draw(e);
		it_list_win = e->ui.list_win;
		while (it_list_win)
		{
			SDL_UpdateWindowSurface(it_list_win->win);
			it_list_win = it_list_win->next;
		}
	}
	rt_exit(e);
}
