/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 18:00:25 by kdouveno          #+#    #+#             */
/*   Updated: 2018/12/14 15:30:10 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEO3D_H
# define GEO3D_H
# include <math.h>
# include "msgs.h"

typedef struct		s_3d
{
	double	x;
	double	y;
	double	z;
}					t_3d;

typedef t_3d	t_vec;
typedef t_3d	t_pt;
typedef t_3d	t_rot;


typedef struct		s_rgb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}					t_rgb;

typedef	union		u_color
{
	t_rgb			p;
	unsigned int	i;
}					t_color;

typedef struct		s_line
{
	t_pt	m;
	t_vec	v;
}					t_line;

typedef enum		e_polyres_type
{
	NORES, ONERES, TWORES
}					t_polyres_type;

typedef struct		s_polyres
{
	t_polyres_type	type;
	double			a;
	double			b;
}					t_polyres;

typedef struct		s_loc
{
	int				id;
	int				lock;
	t_pt			pt;
	void			*target;
}					t_loc;


t_3d			xrot(t_3d td, double a);
t_3d			yrot(t_3d td, double a);
t_3d			zrot(t_3d td, double a);
t_3d			rot(t_3d td, t_rot r);
t_3d			unrot(t_3d td, t_rot r);

t_vec				get_vector(t_pt a, t_pt b);
t_line				get_line(t_pt a, t_pt b);
t_pt				get_linept(t_line d, double t);

t_vec				normalise(t_vec v);
t_vec				vecpro(t_vec v, double a);
t_vec				vec_rev(t_vec v);
t_pt				apply(t_vec v, t_pt p);
double				angle(t_vec a, t_vec b);
double				scalar_product(t_vec a, t_vec b);
t_rot				get_rot(t_vec a, double x);

t_color				rgbpro(t_color c, double m);
t_color				rgbadd(t_color c1, t_color c2);
t_color				rgbmin(t_color c1, t_color c2);
t_color				rgbneg(t_color c);
t_color				rgbmid(t_color c1, t_color c2, float mid);
t_color				rgbmoy4(t_color c[4]);


double				rad(double deg);
double				deg(double rad);
double				sq(double a);

#endif
