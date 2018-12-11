/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_calls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 04:59:25 by schaaban          #+#    #+#             */
/*   Updated: 2018/12/11 16:01:40 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				b_call_menu_cam(void *e, int n)
{
	(void)n;
	((t_env*)e)->ui.gui.actual_menu = ((t_env*)e)->ui.gui.menu_cam;
}

void				b_call_menu_main(void *e, int n)
{
	(void)n;
	((t_env*)e)->ui.gui.actual_menu = ((t_env*)e)->ui.gui.menu_main;
}

void				b_call_exit(void *e, int n)
{
	(void)n;
	rt_exit((t_env*)e);
}

void				b_call_open_win(void *e, int n)
{
	char	*title;
	char	*number;
	t_cam	*c;

	if (!(number = ft_itoa(n)))
		error((t_env*)e, MALLOC_ERROR);
	if (!(title = ft_strjoin("RTv2 - Camera ", number)))
	{
		ft_strdel(&number);
		error((t_env*)e, MALLOC_ERROR);
	}
	ft_strdel(&number);
	n--;
	c = render_cam((t_env*)e, n);
	list_win_add((t_env*)e, &(((t_env*)e)->ui.list_win), (t_list_win){0,
		SDL_CreateWindow(title, 0, 0, c->data.dimx, c->data.dimy, 0), NULL, NULL});
	SDL_BlitSurface(c->data.render, NULL,
		((t_env*)e)->ui.list_win->render, NULL);
	ft_strdel(&title);
}
