/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:44:37 by schaaban          #+#    #+#             */
/*   Updated: 2019/01/12 14:32:38 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char			*s_get_win_title(t_env *e)
{
	char	*s;
	char	*number;

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
	return (s);
}

static void			s_create_render_win(t_env *e)
{
	char	*title;
	t_cam	*c;

	e->ui.pbar.value = 0;
	e->ui.is_rendering = 0;
	if (pthread_join(e->ui.th_pb, (void**)&c))
		error(e, THREAD_J_ERROR);
	title = s_get_win_title(e);
	list_win_add(e, &(e->ui.list_win), (t_list_win){0,
		SDL_CreateWindow(title, 0, 0, c->data.dimx, c->data.dimy, 0),
		NULL, e->ui.local_cam_n, NULL});
	SDL_BlitSurface(c->data.render, NULL,
		e->ui.list_win->render, NULL);
	ft_strdel(&title);
}

void				ft_update(t_env *e)
{
	if (e->ui.is_rendering == 2)
		s_create_render_win(e);
	list_btn_cam(e, 1);
	if (e->ui.is_rendering)
		list_btn_update(e, e->ui.gui.actual_menu->list_btn, 2);
	else
	{
		if (e->ui.mouse_win)
		{
			if (e->ui.mouse_win->id == e->ui.id_main_win)
				list_btn_update(e, e->ui.gui.actual_menu->list_btn, 0);
			else
				list_btn_update(e, e->ui.gui.actual_menu->list_btn, 1);
		}
		else
			list_btn_update(e, e->ui.gui.actual_menu->list_btn, 1);
	}
	pbar_update(e);
}
