/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:28:33 by gperez            #+#    #+#             */
/*   Updated: 2018/11/05 20:09:30 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		error(t_env *e, const char *msg)
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
		d->dimx = DIMX;
		d->dimy = DIMY;
		d->xmax = d->dimx * d->antialia;
		d->ymax = d->dimy * d->antialia;
		d->vp_ul = rot((t_vec){(double)(d->xmax / 2) / tan(d->fov / 2),
			d->xmax / 2, d->ymax / 2}, cams->dir);
		d->x = rot((t_vec){0, -1, 0}, cams->dir);
		d->y = rot((t_vec){0, d->xmax - 1, -1}, cams->dir);
		if (!(d->render = SDL_CreateRGBSurface(0, d->xmax, d->ymax,
		32, RMASK, GMASK, BMASK, AMASK)))
			error(e, SDL_GetError());
		cams = cams->next;

	}
}

static void init_objs(t_env *e) {
	t_obj	*objs;

	objs = e->s.objs;
	while (objs)
	{
		if (objs->type == CONE)
			objs->v1 = rad(objs->v1);
		objs = objs->next;
	}
}
/*
static Uint32        s_get_rgba(Uint32 base_color, t_cam_render *rt)
{
	return (SDL_MapRGBA(rt->render->format,
		(base_color & 0xff0000) >> 16,
		(base_color & 0xff00) >> 8,
		(base_color & 0xff),
		(base_color & 0xff000000) >> 24));
}

static void            ft_put_pixel(int x, int y, Uint32 c, t_cam_render *rt)
{
	Uint8 *p;

	c = s_get_rgba(c, rt);
	p = (Uint8*)rt->render->pixels + y * rt->render->pitch
	+ x * rt->render->format->BytesPerPixel;
	*(Uint32*)p = c;
	if (rt->render->format->BytesPerPixel == 1)
	*p = c;
	else if (rt->render->format->BytesPerPixel == 2)
	*(Uint16*)p = c;
	else if (rt->render->format->BytesPerPixel == 3)
	{
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (c >> 16) & 0xff;
			p[1] = (c >> 8) & 0xff;
			p[2] = c & 0xff;
		}
		else
		{
			p[0] = c & 0xff;
			p[1] = (c >> 8) & 0xff;
			p[2] = (c >> 16) & 0xff;
		}
	}
}
*/
void	*render(void *r)
{
	int				ix;
	int				iy;
	t_line			l;
	t_cam_render	*d;

	iy = 0;
	d = &((t_rendering*)r)->c->data;
	while (d->iy < d->ymax - 1)
	{
		pthread_mutex_lock(&((t_rendering*)r)->lock);
		ix = d->ix++;
		iy = d->iy;
		l = (t_line){((t_rendering*)r)->c->t, d->vp_ul};
		if (d->ix >= d->xmax)
		{
			d->ix = 0;
			d->iy++;
			d->vp_ul = apply(d->y, d->vp_ul);
		}
		else
			d->vp_ul = apply(d->x, d->vp_ul);
		t_color c = raytrace(r, l);
		((int*)d->render->pixels)[iy * d->xmax + ix] = c.i;
	}
	pthread_exit(NULL);
	return (NULL);
}

t_cam	*render_cam(t_env *e, int ncam)
{
	t_rendering		r;
	pthread_t		thds[THRD_CNT];
	int				i;
	t_cam			*c;

	r.lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	r.e = e;
	i = 0;
	c = e->s.cams;
	while (i++ < ncam && c)
		c = c->next;
	if (!c)
		return (NULL);
	r.c = c;
	i = 0;
	while (i < THRD_CNT)
	{
		if (pthread_create(thds + i, NULL, &render, &r))
			error(e, PTHR_ERROR);
		i++;
	}
	while (i >= 0)
		pthread_join(thds[i--], NULL);
	return (c);
}

/*void print_surface_pixels(SDL_Surface *s)
{
	t_color	*pixels = (t_color*)s->pixels;
	int	length = s->w * s->h;
	int i = 0;
	while (i < length)
	{
		if (pixels[i].i & 0x11111100)
		printf("argb(%hhu, %hhu, %hhu, %hhu)\n", pixels[i].p.a, pixels[i].p.r, pixels[i].p.g, pixels[i].p.b);
		i++;
	}
	printf("Surface (%d, %d; %d)\n\n", s->w, s->h, length);
}*/

void	ft_window(t_env *e)
{
	SDL_Surface	*sur;
	SDL_Surface	*sur1;

	if (SDL_Init(SDL_INIT_EVERYTHING))
		error(e, SDL_ERROR);
	e->glb.win = SDL_CreateWindow("RT - UI",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		DIMX, DIMY, SDL_WINDOW_SHOWN);
	init_cam(e);
	init_objs(e);
	sur = render_cam(e, 0)->data.render;
	sur1 = SDL_GetWindowSurface(e->glb.win);
	//print_surface_pixels(sur);
	SDL_BlitSurface(sur, NULL, sur1, &((SDL_Rect){0, 0, DIMX, DIMY}));
	SDL_UpdateWindowSurface(e->glb.win);
}

int		main(int argc, char **argv)
{
	t_env		e;

	arg(&e, argc, argv);
	ft_window(&e);
	getchar();
	free_env(&e);
	return (0);
}
