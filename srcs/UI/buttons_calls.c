/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_calls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 04:59:25 by schaaban          #+#    #+#             */
/*   Updated: 2018/12/10 05:00:25 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtui.h"

void				b_call_menu_cam(t_rt *rt, int n)
{
	(void)n;
	rt->gui.actual_menu = rt->gui.menu_cam;
}

void				b_call_menu_main(t_rt *rt, int n)
{
	(void)n;
	rt->gui.actual_menu = rt->gui.menu_main;
}

void				b_call_exit(t_rt *rt, int n)
{
	(void)n;
	rt_exit(rt);
}

void				b_call_open_win(t_rt *rt, int n)
{
	char	*title;
	char	*number;

	if (!(number = ft_itoa(n)))
		error(rt, MALLOC_ERROR);
	if (!(title = ft_strjoin("RTv2 - Camera ", number)))
	{
		ft_strdel(&number);
		error(rt, MALLOC_ERROR);
	}
	ft_strdel(&number);
	list_win_add(rt, &(rt->list_win), (t_list_win){0,
		SDL_CreateWindow(title, 0, 0, 600, 350, 0), NULL, NULL});
	ft_clear_screen(0xffff0000, rt->list_win);
	ft_strdel(&title);
}
