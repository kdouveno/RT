/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_link_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:19:41 by gperez            #+#    #+#             */
/*   Updated: 2018/11/12 17:19:49 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	link_texture(t_env *e, t_obj *obj, char *file)
{
	if (!file)
		error(e, MALLOC_ERROR);
	if (!(obj->mat.txt = SDL_LoadBMP(file)))
	{
		ft_putendl("\033[38;5;203m"TEXT_ERROR"\033[0m");
		obj->mat.txt = SDL_CreateRGBSurface(0, 0, 0, 32,
			RMASK, GMASK, BMASK, AMASK);
		obj->mat.txt->userdata = "none";
	}
	else
		obj->mat.txt->userdata = "fill";
}
