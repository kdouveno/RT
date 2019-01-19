/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_perlin_noise.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 17:38:39 by gperez            #+#    #+#             */
/*   Updated: 2019/01/19 16:19:24 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	rand_noise(int t)
{
	t = (t << 9) ^ t;
	t = t * (t * (t * t * 15731 + 789221) + 1376312589);
	return ((t & 0xffffffff) / (double)0xffffffff);
}

static double	noise_3d(int x, int y, int z)
{
	return (rand_noise(rand_noise(rand_noise(x) * 850000 + y)
		* 850000 + z) * 850000);
}

static int		noise(int octavs, double frequency, double persistence, t_pt pt)
{
	double	out;
	double	amplitude;
	int		i;

	out = 0.0f;
	amplitude = 1.0f;
	i = 0;
	while (i < octavs)
	{
		out += noise_3d(pt.x * frequency, pt.y * frequency,
			pt.z * frequency) * amplitude;
		amplitude *= persistence;
		frequency *= 2;
		i++;
	}
	return (out);
}

t_color			perlin_noise(t_pt pt)
{
	t_color	out;
	int		perlin_noise;

	perlin_noise = noise(7, 1, 0.8, pt);
	out.p.a = 0xFF;
	out.p.r = (char)perlin_noise;
	out.p.g = (char)perlin_noise;
	out.p.b = (char)perlin_noise;
	return (out);
}
