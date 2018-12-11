/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 15:16:05 by schaaban          #+#    #+#             */
/*   Updated: 2018/11/11 05:53:03 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtui.h"

static Uint32		s_get_rgba(Uint32 base_color, t_list_win *win)
{
	return (SDL_MapRGBA(win->render->format,
		(base_color & 0xff0000) >> 16,
		(base_color & 0xff00) >> 8,
		(base_color & 0xff),
		(base_color & 0xff000000) >> 24));
}

void				ft_put_pixel(int x, int y, Uint32 c, t_list_win *win)
{
    Uint8 *p;


	c = s_get_rgba(c, win);
	p = (Uint8*)win->render->pixels + y * win->render->pitch
		+ x * win->render->format->BytesPerPixel;
    *(Uint32*)p = c;
	if (win->render->format->BytesPerPixel == 1)
		*p = c;
	else if (win->render->format->BytesPerPixel == 2)
		*(Uint16*)p = c;
	else if (win->render->format->BytesPerPixel == 3)
	{
		p[0] = (c >> 16) & 0xff;
		p[1] = (c >> 8) & 0xff;
		p[2] = c & 0xff;
	}
}

void				ft_clear_screen(Uint32 color, t_list_win *win)
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
			ft_put_pixel(j, i, color, win);
	}
}
