/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:28:33 by gperez            #+#    #+#             */
/*   Updated: 2019/01/20 17:53:22 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

inline static void	s_init_ptrs(t_env *e)
{
	int		i;

	i = -1;
	while (++i < 10)
		e->ui.digits[i] = NULL;
	e->ui.list_win = NULL;
	e->ui.focus_win = NULL;
	e->ui.mouse_win = NULL;
	e->ui.gui.menu_main = NULL;
	e->ui.gui.menu_cam = NULL;
	e->ui.pbar.frame = NULL;
	e->ui.pbar.fill = NULL;
	e->ui.btn_gray = NULL;
}

static char			*get_file_name(char *path)
{
	int		i;

	i = ft_strlen(path) - 1;
	while (i > -1)
	{
		if (path[i] == '/')
			break ;
		i--;
	}
	return (path + i + 1);
}

int					main(int argc, char **argv)
{
	t_env		e;

	if (argc == 1)
	{
		ft_putendl("\033[38;5;203m"USAGE);
		return (0);
	}
	s_init_ptrs(&e);
	e.glb.d = arg(&e, argc, argv);
	e.ui.file_name = get_file_name(argv[1]);
	init(&e);
	rtui_init(&e);
	sdl_loop(&e);
	return (0);
}
