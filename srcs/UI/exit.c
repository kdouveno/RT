/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 00:27:13 by schaaban          #+#    #+#             */
/*   Updated: 2018/12/04 14:13:12 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			s_free_sdl(t_env *e)
{
	int		i;

	i = -1;
	while (++i < 10)
	{
		if (e->ui.digits[i])
			SDL_FreeSurface(e->ui.digits[i]);
	}
	if (e->ui.win)
		SDL_DestroyWindow(e->ui.win);
}

void				rt_exit(t_env *e)
{
	s_free_sdl(e);
	list_win_del(e->ui.list_win);
	list_btn_del(e->ui.gui.menu_main->list_btn);
	if (e->ui.gui.menu_main)
		ft_memdel((void**)&(e->ui.gui.menu_main));
	list_btn_del(e->ui.gui.menu_cam->list_btn);
	if (e->ui.gui.menu_cam)
		ft_memdel((void**)&(e->ui.gui.menu_cam));
	SDL_Quit();
	exit(0);
}