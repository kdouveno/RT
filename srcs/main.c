/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:28:33 by gperez            #+#    #+#             */
/*   Updated: 2018/10/26 17:56:04 by kdouveno         ###   ########.fr       */
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
	t_vec	vp_ul;

	cams = e->s.cams;
	dist = (double)(DIMX / 2) / tan(rad(FOV / 2));
	while (cams != NULL)
	{
		if (cams->r >= 0)
			cams->dir = get_rot(cams->dir, cams->r);
		else
			cams->dir = (t_three_d){rad(cams->dir.x), rad(cams->dir.y), rad(cams->dir.z)};
		vp_ul = (t_vec){dist, -DIMX *  / 2, -DIMY / 2};
		vp_ul = rot(vp_ul, cams->dir);
		cams->data = (t_cam_render){vp_ul,
			rot((t_vec){0, -1, 0}, cams->dir),
			rot((t_vec){0, 0, -1}, cams->dir), 0, 0};
		cams = cams->next;
	}
}

raytrace(t_rendering *e, t_line l, int aa, double m)
{
	if (aa)
	{
		return (apply(l, vec_pro(e->c->)))
	}
}

void	render(t_rendering *r)
{
	int		ix;
	int		iy;

	pthread_mutex_lock(&r->lock);
	raytrace();
}

void	start_rendering(t_env *e, int ncam)
{
	t_rendering		r;
	pthread_t		thds[THRD_CNT];
	int				i;
	t_cam			*c;

	r.lock = PTHREAD_MUTEX_INITIALIZER;
	r.e = e;
	i = 0;
	while (i < ncam && c)
	{
		c = c->next;
		i++;
	}
	!c ? return :;
	r.c = c;
	while (i < THRD_CNT)
	{
		if (pthread_create(thds + i, NULL, &render, &(ncam)))
			error(e, PTHR_ERROR);
		i++;
	}
	while (i >= 0)
	{
		pthread_join(thds + i, NULL);
		i--;
	}
}

static void	ft_window(t_env *e)
{
	if ((e->glb.ptr = mlx_init()) == NULL
	|| (e->glb.win = mlx_new_window(e->glb.ptr, DIMX,
		DIMY, "RT")) == NULL
	|| (e->glb.iptr = mlx_new_image(e->glb.ptr, DIMX, DIMY)) == NULL
	|| (e->glb.img = (int*)mlx_get_data_addr(e->glb.iptr, e->glb.iarg,
		e->glb.iarg + 1, e->glb.iarg + 2)) == NULL)
		error(e, MLX_ERROR);

	init_cam(e);
	start_rendering(e, 0);
	mlx_put_image_to_window(e->glb.ptr, e->glb.win, e->glb.iptr, 0, 0);
	mlx_hook(e->glb.win, KeyPress, KeyPressMask, my_key, e);
	mlx_loop(e->glb.ptr);
}

int		main(int argc, char **argv)
{
	t_env		e;

	arg(&e, argc, argv);
	ft_window(&e);
	free_env(&e);
	return (0);
}
