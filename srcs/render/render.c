#include "rt.h"

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
