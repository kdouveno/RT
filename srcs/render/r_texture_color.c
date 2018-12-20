/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_texture_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:27:27 by kdouveno          #+#    #+#             */
/*   Updated: 2018/12/20 15:12:44 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	get_text_color(int x, int y, int width, char *pixels)
{
	t_color	out;

	out = (t_color)AMASK;
	out.p.b = *(pixels + 3 * ((int)y * width + (int)x));
	out.p.g = *(pixels + 3 * ((int)y * width + (int)x) + 1);
	out.p.r = *(pixels + 3 * ((int)y * width + (int)x) + 2);
	return (out);
}

t_vec	perturbation(double x, double y, int width, char *pixels)
{
	t_vec	proj;
	t_vec	dir;
	t_pt	p[3];
	t_vec	out;

	dir = normalise((t_vec){1, 1, 0});
	proj = vecpro(dir,
		scalar_product(get_vector((t_pt){(int)x, (int)y, 0}, (t_pt){x, y, 0})
		, dir));
	p[1] = (t_pt){(int)x + 1, (int)y, get_text_color((int)x + 1, (int)y, width, pixels).i};
	p[2] = (t_pt){(int)x, (int)y + 1, get_text_color((int)x, (int)y + 1, width, pixels).i};
	if (get_norm(proj) > sqrt(2) / 2)
		p[0] = (t_pt){(int)x + 1, (int)y + 1, get_text_color((int)x + 1,(int) y + 1, width, pixels).i};
	else
		p[0] = (t_pt){(int)x, (int)y, get_text_color((int)x, (int)y, width, pixels).i};
	out = rot(get_norm_plan(p[0], p[1], p[2]), get_rot((t_rot){M_PI_2, 0, M_PI_2}, 0));
	if (scalar_product(out, (t_vec){1, 0, 0}) < 0)
		out = vec_rev(out);
	return (out);
}

t_color	texture_color(t_obj obj, t_pt pt, t_vec *pert, SDL_Surface *txt)
{
	double	x;
	double	y;
	t_vec	ang;
	t_color	out;
	char	*pixels;

	pixels = txt->pixels;
	ang = get_rot(unrot(get_vector(obj.m.t, pt), obj.m.rot), 0);
	x = ang.z + M_PI;
	y = ang.y + M_PI_2;
	x = (txt->w * x) / (2 * M_PI);
	y = (txt->h * y) / M_PI;

	out = get_text_color(x, y, txt->w, pixels);
	if (pert && obj.mat.txt_bm && !(ft_strcmp(obj.mat.txt_bm->userdata, "fill")))
		*pert = normalise(perturbation(x, y, txt->w, pixels));
	return (out);
}
