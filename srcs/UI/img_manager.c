/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 18:15:06 by schaaban          #+#    #+#             */
/*   Updated: 2018/12/19 04:02:18 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Surface			*sdl_img_import(char *filename)
{
	SDL_Surface		*img;

	if (!(img = SDL_LoadBMP(filename)))
		return (NULL);
	return (img);
}

void				sdl_img_export(SDL_Surface *img, char *filename)
{
	if ((SDL_SaveBMP(img, filename)) == -1)
		return ;
}

void				rt_export_screenshoot(t_env *e, t_list_win *win)
{
	char	*s;
	char	*n;

	if (!(n = ft_itoa(win->cam)))
		error(e, MALLOC_ERROR);
	if (!(s = ft_strjoin(e->ui.file_name, "_")))
	{
		ft_strdel(&n);
		error(e, MALLOC_ERROR);
	}
	if (!(s = ft_strjoin_free(s, n)))
	{
		ft_strdel(&n);
		error(e, MALLOC_ERROR);
	}
	ft_strdel(&n);
	if (!(s = ft_strjoin_free(s, ".bmp")))
		error(e, MALLOC_ERROR);
	sdl_img_export(win->render, s);
	ft_strdel(&s);
}
