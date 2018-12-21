/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_perlin_noise.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 17:38:39 by gperez            #+#    #+#             */
/*   Updated: 2018/12/21 17:41:43 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		rand_noise(int t)
{
	t = (t<<13) ^ t;
	t = (t * (t * t * 15731 + 789221) + 1376312589);
	return (1.0 - (t & 0x7fffffff) / 1073741824.0);
}

double noise_3d(int x, int y, int z)
{
	return (rand_noise(rand_noise(rand_noise(x) * 850000 + y)
		* 850000 + z) * 850000);
}


/*double cosine_interpolate(double a, double b, double t)
{
	double c = (1 - cos(t * 3.1415927)) * .5;

	return (1. - c) * a + c * b;
}

double smooth_noise(double x, double y, double z)
{
	t_3d	integer;
	t_3d	fractional;
	t_vec	v1;
	t_vec	v2;

	integer.x = x >= 0 ? (int)x : (int)x - 1;
	integer.y = y >= 0 ? (int)y : (int)y - 1;
	integer.z = z >= 0 ? (int)z : (int)z - 1;

	//Partie fractionnaire : x - E(x)
	fractional.x = x - integer.x;
	fractional.y = y - integer.y;
	fractional.z = z - integer.z;

	//Bruit des quatre points d'un cube
	double a0 = noise_3d(integer.x, integer.y, integer.z);
	double a1 = noise_3d(integer.x + 1, integer.y, integer.z);

	double b0 = noise_3d(integer.x,     integer.y + 1, integer.z);
	double b1 = noise_3d(integer.x + 1, integer.y + 1, integer.z);

	double c0 = noise_3d(integer.x,     integer.y,     integer.z + 1);
	double c1 = noise_3d(integer.x + 1, integer.y,     integer.z + 1);

	double d0 = noise_3d(integer.x,     integer.y + 1, integer.z + 1);
	double d1 = noise_3d(integer.x + 1, integer.y + 1, integer.z + 1);

	//Interpolation sur la face inférieure du cube :

	v1.x = cosine_interpolate(a0, a1, fractional.x);
	v1.y = cosine_interpolate(b0, b1, fractional.x);
	v1.z = cosine_interpolate(v1.x, v1.y, fractional.y);

	//Interpolation sur la face supérieure du cube :

	v2.x = cosine_interpolate(c0, c1, fractional.x);
	v2.y = cosine_interpolate(d0, d1, fractional.x);
	v2.z = cosine_interpolate(v2.x, v2.y, fractional.y);

	//Interpolation entre les points
	// situés sur chacune des deux faces :
	return (cosine_interpolate(v1.z, v2.z, fractional.z));
}*/

double	perlin(int octaves, double frequency, double persistence, t_pt pt)
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
	return (out * (1 - persistence) / (1 - amplitude));
}

t_color	perlin_noise(t_obj obj, t_pt pt)
{
	t_color	out;
	double	coef;
	char	perlin_out;

	coef = (perlin(10, 15.0f, -1.5f, pt) + 1) / 2.0f;
	perlin_out = coef * 255;
	out.p.a = 0xFF;
	out.p.r = perlin_out;
	out.p.g = perlin_out;
	out.p.b = perlin_out;
	(void)obj;
	return (out);
}
