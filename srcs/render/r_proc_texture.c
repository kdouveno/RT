/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_proc_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:29:24 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/13 14:42:11 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	fill_color_scale_next(t_obj obj, t_color c[2], int *scale)
{
	if (obj.type == 9)
	{
		*scale = (obj.v[0] + obj.v[1] + obj.v[2]) / 6;
		c[0].i = 0x000000;
		c[1].i = 0x00FFFF;
	}
	else
	{
		*scale = 4;
		c[0].i = 0x000000;
		c[1].i = 0xFFFFFF;
	}
}

void	fill_color_scale(t_obj obj, t_color c[2], int *scale)
{
	if (obj.type == 3)
	{
		*scale = obj.v[0] / 2;
		c[0].i = 0x000000;
		c[1].i = 0xFF00FF;
	}
	else if (obj.type == 4)
	{
		*scale = deg(obj.v[0]) / 2;
		c[0].i = 0x000000;
		c[1].i = 0xFFFF00;
	}
	else if (obj.type == 5)
	{
		*scale = obj.v[0] / 2;
		c[0].i = 0x000000;
		c[1].i = 0x00FF00;
	}
	else
		fill_color_scale_next(obj, c, scale);
}

t_color	texture_none(t_obj obj, t_pt pt)
{
	t_color	out;
	t_color	c[2];
	int		scale;

	pt = rtrans_pt(pt, &obj.m);
	scale = 0;
	fill_color_scale(obj, c, &scale);
	if (((int)((pt.y + OFFSET) / scale) % 2 == 0)
		^ ((int)((pt.z + OFFSET) / scale) % 2 == 0)
		^ ((int)((pt.x + OFFSET) / scale) % 2 == 0))
		out = c[0];
	else
		out = c[1];
	return (out);
}

t_color	get_grad_color(t_pt pt, t_grad *grad)
{
	t_vec dir;
	t_vec v;
	t_vec z;
	float t;

	v = get_vector(grad->cpt, pt);
	dir = normalise(grad->r);
	z = vecpro(dir, scalar_product(v, dir));
	if (grad->r.x)
		t = z.x / grad->r.x;
	else if (grad->r.y)
		t = z.y / grad->r.y;
	else if (grad->r.z)
		t = z.z / grad->r.z;
	else
		return (grad->c1);
	if (t < 0)
		t = 0.0;
	else if (t > 1)
		t = 1;
	return (rgbmid(grad->c1, grad->c2, t));
}

t_color	get_pt_color(t_obj obj, t_pt pt, t_vec *pert)
{
	t_color	out;

	out.i = 0;
	if (obj.mat.txt)
	{
		if (!(ft_strcmp(obj.mat.txt->userdata, "none")))
			out = texture_none(obj, pt);
		else if (!(ft_strcmp(obj.mat.txt->userdata, "perlin")))
			out = perlin_noise(pt);
		else if (!(ft_strcmp(obj.mat.txt->userdata, "fill")))
			out = texture_color(obj, pt, NULL, obj.mat.txt);
	}
	else if (obj.grad)
		out = get_grad_color(pt, obj.grad);
	else
		out = obj.mat.color;
	if (obj.mat.txt_bm)
		if (!(ft_strcmp(obj.mat.txt_bm->userdata, "fill")))
			texture_color(obj, pt, pert, obj.mat.txt_bm);
	return (out);
}
