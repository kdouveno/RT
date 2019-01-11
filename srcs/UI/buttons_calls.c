/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_calls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 04:59:25 by schaaban          #+#    #+#             */
/*   Updated: 2019/01/11 13:19:20 by gperez           ###   ########.fr       */
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

void				*s_thread_go(void *e)
{
	char	*s;
	char	*number;
	t_cam	*c;

	if (!(number = ft_itoa(((t_env*)e)->ui.local_cam_n)))
		error((t_env*)e, MALLOC_ERROR);
	if (!(s = ft_strjoin("Camera ", number)))
	{
		ft_strdel(&number);
		error((t_env*)e, MALLOC_ERROR);
	}
	ft_strdel(&number);
	if (!(s = ft_strjoin_free(s, " - ")))
		error((t_env*)e, MALLOC_ERROR);
	if (!(s = ft_strjoin_free(s, ((t_env*)e)->ui.file_name)))
		error((t_env*)e, MALLOC_ERROR);
	c = render_cam(e, ((t_env*)e)->ui.local_cam_n - 1);
	list_win_add((t_env*)e, &(((t_env*)e)->ui.list_win), (t_list_win){0,
		SDL_CreateWindow(s, 0, 0, c->data.dimx, c->data.dimy, 0),
		NULL, ((t_env*)e)->ui.local_cam_n, NULL});
	SDL_BlitSurface(c->data.render, NULL,
		((t_env*)e)->ui.list_win->render, NULL);
	ft_strdel(&s);
	((t_env*)e)->ui.pbar.value = 0;
	pthread_join(((t_env*)e)->ui.th_pb, NULL);
	pthread_exit(NULL);
}

void				b_call_open_win(void *e, int n)
{
	((t_env*)e)->ui.local_cam_n = n;
	pthread_create(&((t_env*)e)->ui.th_pb, NULL, s_thread_go, e);
}
