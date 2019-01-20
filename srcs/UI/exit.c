/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 00:27:13 by schaaban          #+#    #+#             */
/*   Updated: 2019/01/20 17:56:28 by gperez           ###   ########.fr       */
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
	if (e->ui.pbar.frame)
		SDL_FreeSurface(e->ui.pbar.frame);
	if (e->ui.pbar.fill)
		SDL_FreeSurface(e->ui.pbar.fill);
	if (e->ui.btn_gray)
		SDL_FreeSurface(e->ui.btn_gray);
}

void				rt_exit(t_env *e)
{
	e->glb.quit_signal = 1;
	pthread_join(e->ui.th_pb, NULL);
	s_free_sdl(e);
	e->ui.list_win ? list_win_del(e->ui.list_win) : 0;
	if (e->ui.gui.menu_main)
	{
		list_btn_del(e->ui.gui.menu_main->list_btn);
		ft_memdel((void**)&(e->ui.gui.menu_main));
	}
	if (e->ui.gui.menu_cam)
	{
		list_btn_del(e->ui.gui.menu_cam->list_btn);
		ft_memdel((void**)&(e->ui.gui.menu_cam));
	}
	SDL_Quit();
	ft_memdel((void**)&(e->glb.thds));
	free_scene(&(e->s));
	exit(0);
}
