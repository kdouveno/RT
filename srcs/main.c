/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:28:33 by gperez            #+#    #+#             */
/*   Updated: 2018/12/11 15:30:58 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline static void	s_init_ptrs(t_rt *rt)
{
	int		i;

	i = -1;
	while (++i < 10)
		e->ui.digits[i] = NULL;
	e->ui.win = NULL;
	e->ui.render = NULL;
	e->ui.list_win = NULL;
	e->ui.focus_win = NULL;
	e->ui.mouse_win = NULL;
	e->ui.gui.menu_main = NULL;
	e->ui.gui.menu_cam = NULL;
}

int					main(int argc, char **argv)
{
	t_env		e;
	int			d;

	d = arg(&e, argc, argv);
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (0);
	s_init_ptrs(&e);
	rtui_init(&e);
	sdl_loop(&e);
	return (0);
}
