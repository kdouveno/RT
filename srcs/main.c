/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:28:33 by gperez            #+#    #+#             */
/*   Updated: 2018/11/13 17:59:14 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		main(void)
{
	t_env		e;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (0);
	if (!(e.gui.menu_main = (t_menu*)ft_memalloc(sizeof(t_menu))))
		error(&e, MALLOC_ERROR);
	e.gui.menu_main->list_btn = NULL;
	e.gui.menu_main->cam_y = 0;
	if (!(e.gui.menu_cam = (t_menu*)ft_memalloc(sizeof(t_menu))))
		error(&e, MALLOC_ERROR);
	e.gui.menu_cam->list_btn = NULL;
	e.gui.menu_cam->cam_y = 0;
	list_win_add(&e, &(e.list_win), (t_list_win){0,
		SDL_CreateWindow("RT - UI", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, UI_WIDTH, UI_HEIGHT, 0), NULL, NULL});
	e.id_main_win = SDL_GetWindowID(e.list_win->win);
	e.exit = 0;
	sdl_loop(&e);
	return (0);
}
