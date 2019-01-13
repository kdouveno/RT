/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_texture_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:27:27 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/13 14:55:07 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	get_text_color(int x, int y, SDL_Surface *txt, char *pixels)
{
	t_color	out;

	out = (t_color)AMASK;
	x = ((int)x >= txt->w || (int)x < 0) ? 0 : x;
	y = ((int)y >= txt->h || (int)y < 0) ? 0 : y;
	out.p.b = *(pixels + 3 * ((int)y * txt->w + (int)x));
	out.p.g = *(pixels + 3 * ((int)y * txt->w + (int)x) + 1);
	out.p.r = *(pixels + 3 * ((int)y * txt->w + (int)x) + 2);
	return (out);
}

t_vec	perturbation(double x, double y, SDL_Surface *txt, t_obj obj)
{
	t_vec	proj;
	t_vec	dir;
	t_pt	p[3];
	t_vec	out;
	float	lvl;

	lvl = obj.mat.b_lvl;
	dir = normalise((t_vec){1, 1, 0});
	proj = vecpro(dir,
		scalar_product(get_vector((t_pt){0, (int)x,
			(int)-y}, (t_pt){0, x, -y}), dir));
	p[1] = (t_pt){rgb_litlevel(get_text_color((int)x + 1,
		(int)y, txt, (char*)(txt->pixels))) * lvl, (int)x + 1, (int)-y};
	p[2] = (t_pt){rgb_litlevel(get_text_color((int)x,
		(int)y + 1, txt, (char*)(txt->pixels))) * lvl, (int)x, (int)-y - 1};
	if (get_norm(proj) > sqrt(2) / 2)
		p[0] = (t_pt){rgb_litlevel(get_text_color((int)x + 1, (int)y + 1, txt,
			(char*)(txt->pixels))) * lvl, (int)x + 1, (int)-y - 1};
	else
		p[0] = (t_pt){ rgb_litlevel(get_text_color((int)x,
			(int)y, txt, (char*)(txt->pixels))) * lvl, (int)x, (int)-y};
	out = get_norm_plan(p[0], p[1], p[2]);
	if (scalar_product(out, (t_vec){1, 0, 0}) < 0)
		out = rev_3d(out);
	return (out);
}

t_color	texture_color(t_obj obj, t_pt pt, t_vec *pert, SDL_Surface *txt)
{
	pt = rtrans_pt(pt, &obj.m);
	if (obj.type == 4 || obj.type == 5)
		return (cylinder_texture(obj, pt, pert, txt));
	else if (obj.type == 6)
		return (plane_texture(obj, pt, pert, txt));
	else
		return (spherical_texture(obj, pt, pert, txt));
}
