/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_raw_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:27:27 by kdouveno          #+#    #+#             */
/*   Updated: 2018/12/12 11:30:37 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	texture_color(t_obj obj, t_pt pt)
{
	double	x;
	double	y;
	t_vec	ang;
	t_color	out;
	char	*pixels;

	pixels = obj.mat.txt->pixels;
	out = (t_color)AMASK;
	ang = get_rot(unrot(get_vector(obj.t, pt), obj.dir), 0);
	x = ang.z + M_PI;
	y = ang.y + M_PI_2;
	x = (obj.mat.txt->w * x) / (2 * M_PI);
	y = (obj.mat.txt->h * y) / M_PI;

	out.p.b = *(pixels + 3 * ((int)y * obj.mat.txt->w + (int)x));
	out.p.g = *(pixels + 3 * ((int)y * obj.mat.txt->w + (int)x) + 1);
	out.p.r = *(pixels + 3 * ((int)y * obj.mat.txt->w + (int)x) + 2);
	return (out);
}
