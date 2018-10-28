/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:28:33 by gperez            #+#    #+#             */
/*   Updated: 2018/10/28 20:03:03 by kdouveno         ###   ########.fr       */
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
	t_cam			*cams;
	t_cam_render	*d;

	cams = e->s.cams;
	while (cams != NULL)
	{
		d = &cams->data;
		if (cams->r >= 0)
			cams->dir = get_rot(cams->dir, cams->r);
		else
			cams->dir = (t_three_d){rad(cams->dir.x),
			rad(cams->dir.y), rad(cams->dir.z)};
		d->xmax = d->dimx * d->antialia;
		d->ymax = d->dimy * d->antialia;
		d->vp_ul = rot((t_vec){(double)(d->xmax / 2) / tan(rad(d->fov / 2)),
			-d->xmax / 2, -d->ymax / 2}, cams->dir);
		d->x = rot((t_vec){0, -1, 0}, cams->dir);
		d->y = rot((t_vec){0, d->xmax - 1, -1}, cams->dir);
		if (!(d->win = mlx_new_window(e->glb.ptr, d->dimx, d->dimy, "RT"))
		|| !(d->iptr = mlx_new_image(e->glb.ptr, d->xmax * d->antialia,
		d->ymax * d->antialia))
		|| !(d->img = (int*)mlx_get_data_addr(d->iptr, d->iarg, d->iarg + 1,
		d->iarg + 2)))
			error(e, MALLOC_ERROR);
		cams = cams->next;
	}
}

t_color	raytrace(t_rendering *r, t_line l)
{
	(void)r;
	(void)l;
	pthread_mutex_unlock(&r->lock);
	return ((t_color)0);
}

void	render(t_rendering *r)
{
	int				ix;
	int				iy;
	t_line			l;
	t_cam_render	*d;

	d = &r->c->data;
	pthread_mutex_lock(&r->lock);
	ix = d->ix++;
	iy = d->iy;
	l = (t_line){r->c->t, d->vp_ul};
	if (d->ix >= d->xmax)
	{
		d->ix = 0;
		d->iy++;
		d->vp_ul = apply(d->y, d->vp_ul);
	}
	else
		d->vp_ul = apply(d->x, d->vp_ul);
	d->img[d->xmax * iy + ix] = raytrace(r, l).i;
	if (iy < d->ymax - 1)
		render(r);
	pthread_exit(NULL);
}

void	symvoid(void)
{
}


void	start_rendering(t_env *e, int ncam)
{
	t_rendering		r;
	pthread_t		thds[THRD_CNT];
	int				i;
	t_cam			*c;

	r.lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	r.e = e;
	i = 0;
	while (i < ncam && c)
	{
		c = c->next;
		i++;
	}
	if (!c)
		return ;
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
	if ((e->glb.ptr = mlx_init()) == NULL)

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
