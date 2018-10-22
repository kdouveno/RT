/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:28:33 by gperez            #+#    #+#             */
/*   Updated: 2018/10/18 18:28:51 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		error(t_env *e, char *msg)
{
	(void)e;
	ft_putstr("\033[38;5;203m");
	ft_putendl(msg);
	ft_putstr("\033[0m");
	free_env(e);
	exit(0);
}

static void	init_cam(t_env *e)
{
	t_cam	*cams;
	double	dist;

	cams = e->s.cams;
	dist = (double)(DIMX / 2) / tan(rad(FOV / 2));
	while (cams != NULL)
	{
		cams->fov = FOV;
		cams->dir = (t_vec){0, 0, dist};
		cams->vp_ul = apply(cams->t, apply(cams->dir,
			(t_vec){-DIMX / 2, DIMY / 2, 0}));
		cams = cams->next;
	}
}

static void	ft_window(t_env *e)
{
	/*if ((e->mlx.ptr = mlx_init()) == NULL
	|| (e->mlx.win = mlx_new_window(e->mlx.ptr, DIMX,
		DIMY, "RT")) == NULL
	|| (e->mlx.imgptr = mlx_new_image(e->mlx.ptr, DIMX, DIMY)) == NULL
	|| (e->mlx.img = (int*)mlx_get_data_addr(e->mlx.imgptr, e->mlx.imgarg,
		e->mlx.imgarg + 1, e->mlx.imgarg + 2)) == NULL)
		error(e, MLX_ERROR);
	*/
	init_cam(e);
	/*
	mlx_put_image_to_window(e->mlx.ptr, e->mlx.win, e->mlx.imgptr, 0, 0);
	mlx_hook(e->mlx.win, KeyPress, KeyPressMask, my_key, e);
	mlx_loop(e->mlx.ptr);
*/}

int		main(int argc, char **argv)
{
	t_env		e;

	arg(&e, argc, argv);
	ft_window(&e);
	free_env(&e);
	return (0);
}
