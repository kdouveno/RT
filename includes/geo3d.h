/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 18:00:25 by kdouveno          #+#    #+#             */
/*   Updated: 2018/09/25 16:03:10 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEO3D_H
# define GEO3D_H
# include <math.h>

typedef struct		s_three_d
{
	double	x;
	double	y;
	double	z;
}					t_three_d;

typedef t_three_d	t_vec;
typedef t_three_d	t_pt;
typedef t_three_d	t_rot;
typedef struct		s_matrix
{
	double			a;
	double			b;
	double			c;
	double			d;
	double			e;
	double			f;
	double			g;
	double			h;
	double			i;
}					t_matrix;

typedef enum		e_geotype
{
	TYPE_END, CAMERA, LIGHT, SPHERE, CONE, CYLINDER, PLANE
}					t_geotype;

typedef struct		s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}					t_rgb;

typedef	union		u_color
{
	t_rgb			p;
	int				i;
}					t_color;

typedef struct		s_cam
{
	t_pt			t;
	t_vec			dir;
	t_vec			x;
	t_vec			y;
}					t_cam;

typedef struct		s_lit
{
	t_pt			t;
	float			power;
	t_color			color;
	t_color			comp;
	struct s_lit	*next;
}					t_lit;

typedef struct		s_line
{
	t_pt	m;
	t_vec	v;
}					t_line;

typedef struct		s_obj
{
	t_geotype		type;
	t_pt			t;
	t_rot			r;
	double			v;
	t_color			color;
	float			shine;
	struct s_obj	*next;
}					t_obj;

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

typedef struct		s_insecres
{
	t_obj			*obj;
	double			t;
}					t_insecres;

void				print_trix(t_matrix a);
t_matrix			xxadd(t_matrix a, t_matrix b);
t_matrix			xxminus(t_matrix a, t_matrix b);
t_matrix			xxmulti(t_matrix a, t_matrix b);

t_three_d			xrot(t_three_d td, double a);
t_three_d			yrot(t_three_d td, double a);
t_three_d			zrot(t_three_d td, double a);
t_three_d			rot(t_three_d td, t_rot r);
t_three_d			unrot(t_three_d td, t_rot r);

t_vec				get_vector(t_pt a, t_pt b);
t_line				get_line(t_pt a, t_pt b);
t_pt				get_linept(t_line d, double t);
t_color				get_color(t_color c, double m);

t_vec				normalise(t_vec in);
t_vec				vecpro(t_vec v, double a);
t_vec				vec_rev(t_vec v);
t_pt				apply(t_vec v, t_pt p);
double				angle(t_vec a, t_vec b);
double				angle_abs(t_vec a, t_vec b);
double				scalar_product(t_vec a, t_vec b);

double				sphere_line(t_line d, double r);
double				cone_line(t_line d, double a);
double				plane_line(t_line d, double empty);
double				cylinder_line(t_line d, double r);

t_vec				cylinder_norm(t_pt pt, t_obj obj, t_vec v);
t_vec				cone_norm(t_pt pt, t_obj obj, t_vec v);
t_vec				sphere_norm(t_pt pt, t_obj obj, t_vec v);
t_vec				plane_norm(t_pt pt, t_obj obj, t_vec v);

t_color				rgbpro(t_color c, double m);
t_color				rgbadd(t_color c1, t_color c2);
t_color				rgbmin(t_color c1, t_color c2);
t_color				rgbneg(t_color c);
t_color				rgbtrans(t_color c1, t_color c2, double m);
t_color				rgbmoy(t_color c1, t_color c2, double coef);
void				printf_color(t_color c);

double				rad(double deg);
double				deg(double rad);
double				sq(double a);

#endif
