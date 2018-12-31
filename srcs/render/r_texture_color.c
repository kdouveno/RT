/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_texture_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:27:27 by kdouveno          #+#    #+#             */
/*   Updated: 2018/12/21 14:19:53 by gperez           ###   ########.fr       */
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
	float	lvl;

	lvl = BMP_LEVEL;
	dir = normalise((t_vec){1, 1, 0});
	proj = vecpro(dir,
		scalar_product(get_vector((t_pt){0, (int)x, (int)-y}, (t_pt){0 ,x, -y})
		, dir));
	p[1] = (t_pt){rgb_litlevel(get_text_color((int)x + 1, (int)y, width, pixels)) * lvl, (int)x + 1, (int)-y};
	p[2] = (t_pt){rgb_litlevel(get_text_color((int)x, (int)y + 1, width, pixels)) * lvl, (int)x, (int)-y - 1};
	if (get_norm(proj) > sqrt(2) / 2)
		p[0] = (t_pt){rgb_litlevel(get_text_color((int)x + 1,(int) y + 1, width, pixels)) * lvl, (int)x + 1, (int)-y - 1};
	else
		p[0] = (t_pt){ rgb_litlevel(get_text_color((int)x, (int)y, width, pixels)) * lvl, (int)x, (int)-y};
	out = get_norm_plan(p[0], p[1], p[2]);
	if (scalar_product(out, (t_vec){1, 0, 0}) < 0)
		out = vec_rev(out);
	return (out);
}

t_color	spherical_texture(t_obj obj, t_pt pt, t_vec *pert, SDL_Surface *txt)
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
	x = (txt->w * x) / (2 * M_PI) + (txt->w * obj.mat.offx / 100);
	y = (txt->h * y) / M_PI + (txt->h * obj.mat.offy / 100);
	if ((int)x > txt->w)
		x = (int)x % txt->w;
	if ((int)y > txt->h)
		y = (int)y % txt->h;
	out = get_text_color(x, y, txt->w, pixels);
	if (pert && obj.mat.txt_bm && !(ft_strcmp(obj.mat.txt_bm->userdata, "fill"))
		&& txt == obj.mat.txt_bm)
		*pert = normalise(perturbation(x, y, txt->w, pixels));
	return (out);
}

t_color	plane_texture(t_obj obj, t_pt pt, t_vec *pert, SDL_Surface *txt)
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
	x = (txt->w * x) / (2 * M_PI) + (txt->w * obj.mat.offx / 100);
	y = (txt->h * y) / M_PI + (txt->h * obj.mat.offy / 100);
	if ((int)x > txt->w)
		x = (int)x % txt->w;
	if ((int)y > txt->h)
		y = (int)y % txt->h;
	out = get_text_color(x, y, txt->w, pixels);
	if (pert && obj.mat.txt_bm && !(ft_strcmp(obj.mat.txt_bm->userdata, "fill"))
		&& txt == obj.mat.txt_bm)
		*pert = normalise(perturbation(x, y, txt->w, pixels));
	return (out);}


t_color	texture_color(t_obj obj, t_pt pt, t_vec *pert, SDL_Surface *txt)
{
	if (obj.type == 3)
		return (spherical_texture(obj, pt, pert, txt));
	else if (obj.type == 6)
		return (plane_texture(obj, pt, pert, txt));
	else
		return (spherical_texture(obj, pt, pert, txt));
}
