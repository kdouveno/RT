/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:28:33 by gperez            #+#    #+#             */
/*   Updated: 2018/11/12 17:20:52 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_window(t_env *e, int d)
{
	SDL_Surface	*sur;
	SDL_Surface	*sur1;

	if (SDL_Init(SDL_INIT_EVERYTHING))
		error(e, SDL_ERROR);
	e->glb.win = SDL_CreateWindow("RT - UI",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		DIMX, DIMY, SDL_WINDOW_SHOWN);
	init(e);
	if (d == 1)
		debug(e->s, 1);
	sur = render_cam(e, 0)->data.render;
	sur1 = SDL_GetWindowSurface(e->glb.win);
	SDL_BlitSurface(sur, NULL, sur1, 0);
	SDL_UpdateWindowSurface(e->glb.win);
}

int		main(int argc, char **argv)
{
	t_env		e;
	int			d;

	d = arg(&e, argc, argv);
	ft_window(&e, d);
	free_scene((&e.s));
	getchar();
	return (0);
}
