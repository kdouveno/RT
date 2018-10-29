/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:28:33 by gperez            #+#    #+#             */
/*   Updated: 2018/10/29 13:51:27 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		error(t_env *e, char *msg)
{
	(void)e;
	ft_putstr("\033[38;5;203m");
	ft_putendl(msg);
	ft_putstr("\033[0m");
	free_scene(&(e->s));
	exit(0);
}

void		error_prst(t_prst *p, char *msg)
{
	ft_putstr("\033[38;5;203m");
	ft_putendl(msg);
	ft_putstr("\033[0m");
	if (p->next)
		error_prst(p->next, msg);
	free_scene(&(p->s));
	ft_memdel((void**)&p);
}

void	free_prst(t_prst *p)
{
	if (p->next)
		free_prst(p->next);
	free_scene(&(p->s));
	ft_memdel((void**)&p);
}

/*static void	init_cam(t_env *e)
{
	t_cam	*cams;

	cams = e->s.cams;
	while (cams != NULL)
	{
		if (cams->r >= 0)
			cams->dir = get_rot(cams->dir, cams->r);
		else
			cams->dir = (t_three_d){rad(cams->dir.x), rad(cams->dir.y), rad(cams->dir.z)};
		cams->vp_ul = (t_vec){(DIMX / 2) / tan(cams->fov / 2), -DIMX / 2, -DIMY / 2};
		cams->vp_ul = rot(cams->vp_ul, cams->dir);
		cams = cams->next;
	}
}*/

/*static void	ft_window(t_env *e)
{
	if ((e->mlx.ptr = mlx_init()) == NULL
	|| (e->mlx.win = mlx_new_window(e->mlx.ptr, DIMX,
		DIMY, "RT")) == NULL
	|| (e->mlx.imgptr = mlx_new_image(e->mlx.ptr, DIMX, DIMY)) == NULL
	|| (e->mlx.img = (int*)mlx_get_data_addr(e->mlx.imgptr, e->mlx.imgarg,
		e->mlx.imgarg + 1, e->mlx.imgarg + 2)) == NULL)
		error(e, MLX_ERROR);

	init_cam(e);

	mlx_put_image_to_window(e->mlx.ptr, e->mlx.win, e->mlx.imgptr, 0, 0);
	mlx_hook(e->mlx.win, KeyPress, KeyPressMask, my_key, e);
	mlx_loop(e->mlx.ptr);
}*/

int		main(int argc, char **argv)
{
	t_env		e;

	e.glb.thread_count = 100;
	arg(&e, argc, argv);
	//ft_window(&e);
	free_scene((&e.s));
	free_prst(e.p);
	return (0);
}
