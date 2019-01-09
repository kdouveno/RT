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
	t = (t << 9) ^ t;
	t = t * (t * (t * t * 15731 + 789221) + 1376312589);
	return ((t & 0xffffffff) / (double)0xffffffff);
}

double	noise_3d(int x, int y, int z)
{
	return (rand_noise(rand_noise(rand_noise(x) * 850000 + y)
		* 850000 + z) * 850000);
}

double cosine_interpolate(double a, double b, double t)
{
	double c = (1 - cos(t * 3.1415927)) * .5;
	return (1. - c) * a + c * b;
}

double smooth_noise(double x, double y, double z)
{
  //Partie entière : E(x)
  int integer_x = (int)x;
  int integer_y = (int)y;
  int integer_z = (int)z;
  //Partie fractionnaire : x - E(x)
  double fractional_x = x - integer_x;
  double fractional_y = y - integer_y;
  double fractional_z = z - integer_z;

  //Bruit des quatre points d'un cube
  double a0 = noise_3d(integer_x,     integer_y,     integer_z);
  double a1 = noise_3d(integer_x + 1, integer_y,     integer_z);

  double b0 = noise_3d(integer_x,     integer_y + 1, integer_z);
  double b1 = noise_3d(integer_x + 1, integer_y + 1, integer_z);

  double c0 = noise_3d(integer_x,     integer_y,     integer_z + 1);
  double c1 = noise_3d(integer_x + 1, integer_y,     integer_z + 1);

  double d0 = noise_3d(integer_x,     integer_y + 1, integer_z + 1);
  double d1 = noise_3d(integer_x + 1, integer_y + 1, integer_z + 1);

  //Interpolation sur la face inférieure du cube :
  double a = cosine_interpolate(a0, a1, fractional_x);
  double b = cosine_interpolate(b0, b1, fractional_x);
  double v = cosine_interpolate(a, b, fractional_y);
  //Interpolation sur la face supérieure du cube :
  double c = cosine_interpolate(c0, c1, fractional_x);
  double d = cosine_interpolate(d0, d1, fractional_x);
  double w = cosine_interpolate(c, d, fractional_y);

  //Interpolation entre les points
  // situés sur chacune des deux faces :
  return cosine_interpolate(v, w, fractional_z);
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
		out += smooth_noise(pt.x * frequency, pt.y * frequency,
			pt.z * frequency) * amplitude;
		amplitude *= persistence;
		frequency *= 2;
		i++;
	}
	return out * ((1 - persistence) / (1 - amplitude));
}

t_color	perlin_noise(t_obj obj, t_pt pt)
{
	t_color	out;
	double	coef;
	char	perlin_out;

	coef = noise(7, 1, 0.8, pt);
	// printf("%f\n", coef);
	perlin_out = coef * 255;
	out.p.a = 0xFF;
	out.p.r = perlin_out;
	out.p.g = perlin_out;
	out.p.b = perlin_out;
	(void)obj;
	return (out);
}
