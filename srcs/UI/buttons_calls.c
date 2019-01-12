/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_calls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 04:59:25 by schaaban          #+#    #+#             */
/*   Updated: 2019/01/12 14:27:39 by schaaban         ###   ########.fr       */
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
	t_cam	*c;

	((t_env*)e)->ui.is_rendering = 1;
	c = render_cam(e, ((t_env*)e)->ui.local_cam_n - 1);
	((t_env*)e)->ui.is_rendering = 2;
	pthread_exit((void*)c);
}

void				b_call_open_win(void *e, int n)
{
	((t_env*)e)->ui.local_cam_n = n;
	pthread_create(&((t_env*)e)->ui.th_pb, NULL, s_thread_go, e);
}
