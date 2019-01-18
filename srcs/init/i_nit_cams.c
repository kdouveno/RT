/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_nit_cams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:58:41 by gperez            #+#    #+#             */
/*   Updated: 2019/01/18 16:58:55 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_cam_vecs(t_cam *cams)
{
	double			step;
	t_cam_render	*d;

	d = &cams->data;
	step = 1;
	d->pt_ul = trans_pt((t_pt){0, 0, 0}, &cams->m);
	if (d->para)
	{
		step = d->fov / d->dimx;
		d->vp_ul = trans_vec((t_vec){1, 0, 0}, &cams->m);
		d->pt_ul = apply(trans_vec((t_vec){0, d->fov / 2, d->dimy * step / 2},
			&cams->m), d->pt_ul);
	}
	else
		d->vp_ul = trans_vec((t_vec){(double)(d->dimx / 2)
			/ tan(rad(d->fov) / 2), d->dimx / 2, d->dimy / 2}, &cams->m);
	d->x = trans_vec((t_vec){0, -step, 0}, &cams->m);
	d->y = trans_vec((t_vec){0, 0, -step}, &cams->m);
	d->xy = trans_vec((t_vec){0, step * (d->dimx - 1), -step}, &cams->m);
}

void		init_cam(t_env *e, t_scene *s)
{
	t_cam			*cams;
	t_cam_render	*d;

	cams = s->cams;
	while (cams)
	{
		d = &cams->data;
		link_locs(s, cams);
		check_link_loop(e, &cams->m, cams->m.l.target);
		if (cams->m.r >= 0)
			cams->m.rot = get_rot(get_vector(cams->m.pt, cams->m.rot),
			cams->m.r);
		else
			cams->m.rot = (t_3d){rad(cams->m.rot.x),
			rad(cams->m.rot.y), rad(cams->m.rot.z)};
		init_cam_vecs(cams);
		if (!(d->render = SDL_CreateRGBSurface(0, d->dimx, d->dimy,
		32, RMASK, GMASK, BMASK, AMASK)))
			error(e, SDL_GetError());
		cams = cams->next;
	}
}
