/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_calls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 04:59:25 by schaaban          #+#    #+#             */
/*   Updated: 2018/12/11 15:26:11 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				b_call_menu_cam(t_env *e, int n)
{
	(void)n;
	e->ui.gui.actual_menu = e->ui.gui.menu_cam;
}

void				b_call_menu_main(t_env *e, int n)
{
	(void)n;
	e->ui.gui.actual_menu = e->ui.gui.menu_main;
}

void				b_call_exit(t_env *e, int n)
{
	(void)n;
	rt_exit(e);
}

void				b_call_open_win(t_env *e, int n)
{
	char	*title;
	char	*number;

	if (!(number = ft_itoa(n)))
		error(e, MALLOC_ERROR);
	if (!(title = ft_strjoin("RTv2 - Camera ", number)))
	{
		ft_strdel(&number);
		error(e, MALLOC_ERROR);
	}
	ft_strdel(&number);
	list_win_add(e, &(e->ui.list_win), (t_list_win){0,
		SDL_CreateWindow(title, 0, 0, 600, 350, 0), NULL, NULL});
	ft_clear_screen(0xffff0000, e->ui.list_win);
	ft_strdel(&title);
}
