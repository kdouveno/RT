/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:28:33 by gperez            #+#    #+#             */
/*   Updated: 2018/10/30 17:14:28 by kdouveno         ###   ########.fr       */
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
	SDL_Quit();
	exit(0);
}

/*
**	to protect
*/

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
		if (!(d->render = SDL_CreateRGBSurfaceWithFormat(0, d->xmax, d->ymax,
		32, SDL_PIXELFORMAT_ARGB32)))
			error(e, SDL_GetError());
		cams = cams->next;
	}
}

t_color	raytrace(t_rendering *r, t_line l)
{
	(void)r;
	(void)l;
	pthread_mutex_unlock(&r->lock);
	return ((t_color)(r->c->d.iy * r->c->d.xmax + r->c->d->ix));
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
	d->img->pixels[d->xmax * iy + ix] = raytrace(r, l).i;
	if (iy < d->ymax - 1)
		render(r);
	pthread_exit(NULL);
}

t_cam	render_cam(t_env *e, int ncam)
{
	t_rendering		r;
	pthread_t		thds[THRD_CNT];
	int				i;
	t_cam			*c;

	r.lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	r.e = e;
	i = 0;
	while (i++ < ncam && c)
		c = c->next;
	if (!c)
		return (NULL);
	r.c = c;
	while (i < THRD_CNT)
		if (pthread_create(thds + i++, NULL, (void*)&r, &(ncam)))
			error(e, PTHR_ERROR);
	while (i >= 0)
		pthread_join(thds[i--], NULL);
	return (c);
}

static void	ft_window(t_env *e)
{
	if (!SDL_Init(SDL_INIT_VIDEO))
		error(e, SDL_ERROR);
	e->glb.win = SDL_CreateWindow("RT - UI",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1600, 900, SDL_WINDOW_SHOWN);
	init_cam(e);
	render_cam(e, 0);
}

int		main(int argc, char **argv)
{
	t_env		e;

	arg(&e, argc, argv);
	ft_window(&e);
	free_env(&e);
	return (0);
}
