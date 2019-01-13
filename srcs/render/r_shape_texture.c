/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_shape_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 17:06:43 by gperez            #+#    #+#             */
/*   Updated: 2019/01/11 17:45:33 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	offset_txt(t_obj obj, double *x, double *y, SDL_Surface *txt)
{
	int		divi;

	obj.mat.offy = obj.type == 6 ? obj.mat.offy / 100.0f : obj.mat.offy / 50.0f;
	*x = *x + ((double)txt->w * (obj.mat.offx / 100.0f));
	*y = *y + ((double)txt->h * obj.mat.offy);
	if ((int)*x >= txt->w)
		*x = (int)*x % txt->w;
	if ((int)*y >= txt->h)
	{
		divi = (int)*y / txt->h;
		*y = (int)*y % txt->h;
		if (divi % 2 > 0 && obj.type != 6)
		{
			*y = (int)(txt->h - *y);
			*x = (int)(*x + txt->w / 2) % txt->w;
		}
	}
}

t_color	spherical_texture(t_obj obj, t_pt pt, t_vec *pert, SDL_Surface *txt)
{
	double	x;
	double	y;
	t_vec	ang;
	t_color	out;

	ang = get_rot(pt, 0);
	x = ang.z + M_PI;
	y = ang.y + M_PI_2;
	x = (txt->w * x) / (2 * M_PI);
	y = (txt->h * y) / M_PI;
	if (txt != obj.mat.txt_bm)
		offset_txt(obj, &x, &y, txt);
	out = get_text_color(x, y, txt, (char*)(txt->pixels));
	if (pert && obj.mat.txt_bm && !(ft_strcmp(obj.mat.txt_bm->userdata, "fill"))
		&& txt == obj.mat.txt_bm)
		*pert = normalise(perturbation(x, y, txt, obj));
	return (out);
}

t_color	cylinder_texture(t_obj obj, t_pt pt, t_vec *pert, SDL_Surface *txt)
{
	double	x;
	double	y;
	t_vec	ang;
	t_color	out;

	ang = get_rot(pt, 0);
	x = ang.z + M_PI;
	y = -pt.z * 6;
	x = (txt->w * x) / (2 * M_PI);
	if ((int)y >= txt->h)
		y = (int)y % txt->h;
	else if ((int)y < 0)
		y = txt->h - ((int)-y % txt->h);
	if (txt != obj.mat.txt_bm)
		offset_txt(obj, &x, &y, txt);
	out = get_text_color(x, y, txt, (char*)(txt->pixels));
	if (pert && obj.mat.txt_bm && !(ft_strcmp(obj.mat.txt_bm->userdata, "fill"))
		&& txt == obj.mat.txt_bm)
		*pert = normalise(perturbation(x, y, txt, obj));
	return (out);
}

t_color	plane_texture(t_obj obj, t_pt pt, t_vec *pert, SDL_Surface *txt)
{
	double	x;
	double	y;
	t_color	out;

	x = -pt.y * 10;
	y = -pt.z * 10;
	if ((int)x >= txt->w)
		x = (int)x % txt->w;
	else if ((int)x < 0)
		x = txt->w - ((int)-x % -txt->w);
	if ((int)y >= txt->h)
		y = (int)y % txt->h;
	else if ((int)y < 0)
		y = txt->h - ((int)-y % txt->h);
	if (txt != obj.mat.txt_bm)
		offset_txt(obj, &x, &y, txt);
	out = get_text_color(x, y, txt, (char*)(txt->pixels));
	if (pert && obj.mat.txt_bm && !(ft_strcmp(obj.mat.txt_bm->userdata, "fill"))
		&& txt == obj.mat.txt_bm)
		*pert = normalise(perturbation(x, y, txt, obj));
	return (out);
}
