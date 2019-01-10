/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_perlin_noise.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 17:38:39 by gperez            #+#    #+#             */
/*   Updated: 2019/01/10 13:36:19 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		rand_noise(int t)
{
	t = (t << 9) ^ t;
	t = t * (t * (t * t * 15731 + 789221) + 1376312589);
	return ((t & 0xffffffff) / (double)0xffffffff);
}

double	noise_3d(int x, int y, int z)
{
	return (rand_noise(rand_noise(rand_noise(x) * 850000 + y)
		* 850000 + z) * 850000);
}

double	noise(int octaves, double frequency, double persistence, t_pt pt)
{
	double	out;
	double	amplitude;
	int		i;

	out = 0.0f;
	amplitude = 1.0f;
	i = 0;
	while (i < octaves)
	{
		out += noise_3d(pt.x * frequency, pt.y * frequency,
			pt.z * frequency) * amplitude;
		amplitude *= persistence;
		frequency *= 2;
		i++;
	}
	return out * ((1 - persistence) / (1 - amplitude));
}

t_color	perlin_noise(t_pt pt)
{
	t_color	out;
	double	coef;
	char	perlin_out;

	coef = noise(7, 1, 0.8, pt);
	perlin_out = coef * 255;
	out.p.a = 0xFF;
	out.p.r = perlin_out;
	out.p.g = perlin_out;
	out.p.b = perlin_out;
	return (out);
}
