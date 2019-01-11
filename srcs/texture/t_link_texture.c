/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_link_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:19:41 by gperez            #+#    #+#             */
/*   Updated: 2019/01/11 17:03:54 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Surface	*type_text(SDL_Surface *txt, char *file)
{
	if (!(txt = SDL_LoadBMP(file)))
	{
		ft_putendl("\033[38;5;203m"TEXT_ERROR"\033[0m");
		txt = SDL_CreateRGBSurface(0, 0, 0, 32,
			RMASK, GMASK, BMASK, AMASK);
		if (file && !(ft_strcmp(file, "textures/perlin")))
			txt->userdata = "perlin";
		else
			txt->userdata = "none";
	}
	else
		txt->userdata = "fill";
	return (txt);
}

void		link_texture(t_env *e, t_obj *obj, char *file, char type)
{
	if (!file)
	{
		ft_memdel((void**)&file);
		error(e, MALLOC_ERROR);
	}
	if ((obj->mat.txt && type == 't') || (obj->mat.txt_bm && type == 'b'))
		return (wrong_type(e, file, 0, 0));
	if (type == 'b')
		obj->mat.txt_bm = type_text(obj->mat.txt_bm, file);
	else
		obj->mat.txt = type_text(obj->mat.txt, file);
	ft_memdel((void**)&file);
}
