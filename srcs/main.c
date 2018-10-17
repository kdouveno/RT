/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:28:33 by gperez            #+#    #+#             */
/*   Updated: 2018/10/17 12:05:47 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		error(t_env *e, char *msg)
{
	(void)e;
	ft_putstr("\033[38;5;203m");
	ft_putendl(msg);
	ft_putstr("\033[0m");
	exit(0);
}

/*static void	ft_window(t_env *e)
{
	if ((e->mlx.ptr = mlx_init()) == NULL
	|| (e->mlx.win = mlx_new_window(e->mlx.ptr, DIMX,
		DIMY, "RT")) == NULL
	|| (e->mlx.imgptr = mlx_new_image(e->mlx.ptr, DIMX, DIMY)) == NULL
	|| (e->mlx.img = (int*)mlx_get_data_addr(e->mlx.imgptr, e->mlx.imgarg,
		e->mlx.imgarg + 1, e->mlx.imgarg + 2)) == NULL)
		error(e, MLX_ERROR);
	e->cam.fov = FOV;
	e->cam.dist = (double)(DIMX / 2) / tan(rad(FOV / 2));
	e->cam.dir = (t_vec){0, 0, -e->cam.dist};
	e->cam.vp_ul = apply(e->cam.p, apply(e->cam.dir,
		apply((t_vec){0, DIMY / 2, 0}, (t_vec){-DIMX / 2, 0, 0})));
	algo(e);
	mlx_put_image_to_window(e->mlx.ptr, e->mlx.win, e->mlx.imgptr, 0, 0);
	mlx_hook(e->mlx.win, KeyPress, KeyPressMask, my_key, e);
	mlx_loop(e->mlx.ptr);
}*/

int		main(int argc, char **argv)
{
	t_env		e;

	if (argc != 2 && argc != 3)
		error(&e, USAGE);
	parse(&e, argv[1]);
	if (argc == 3 && ft_strcmp(argv[2], "debug") == 0)
		debug(&e);
//	ft_window(&e);
	free_env(&e);
	return (0);
}
