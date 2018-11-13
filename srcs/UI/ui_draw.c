/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 15:16:05 by schaaban          #+#    #+#             */
/*   Updated: 2018/11/13 17:40:24 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				ft_clear_screen(t_color color, t_list_win *win)
{
	int		i;
	int		j;
	int		w;
	int		h;

	i = -1;
	SDL_GetWindowSize(win->win, &w, &h);
	while (++i < h)
	{
		j = -1;
		while (++j < w)
			((int*)win->render->pixels)[i * win->render->w + j] = color.i;
	}
}
