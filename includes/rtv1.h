/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 18:00:40 by kdouveno          #+#    #+#             */
/*   Updated: 2018/09/27 13:10:23 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "mlx.h"
# include "geo3d.h"
# include "libft.h"
# include "gnl.h"
# include <stdlib.h>
# include <stdio.h>
# define DIMX 900
# define DIMY 700

typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
	void		*iptr;
	int			*img;
	int			imgul[3];
}				t_mlx;

typedef struct	s_wininfo
{
	int			x;
	int			y;
}				t_wininfo;

typedef struct	s_scene
{
	t_obj		*objs;
	t_lit		*lits;
	t_cam		cam;
	int			nbrlit;
}				t_scene;

typedef struct	s_env
{
	t_mlx		mlx;
	t_wininfo	w;
	t_scene		s;
}				t_env;

typedef struct	s_set
{
	double			t;
	struct s_set	*next;
}				t_set;

void	parse(t_env *e, char *arg);

typedef struct	s_objfx
{
	t_geotype	type;
	char		funcname[4];
	void		(*parse)(t_env *e, char **line);
	double		(*insec)(t_line d, double a);
	t_vec		(*norm)(t_pt pt, t_obj obj, t_vec v);
}				t_objfx;

void			cylinder_parse(t_env *e, char **line);
void			cone_parse(t_env *e, char **line);
void			sphere_parse(t_env *e, char **line);
void			plane_parse(t_env *e, char **line);
void			light_parse(t_env *e, char **line);
void			camera_parse(t_env *e, char **line);
void			set_camera(t_env *e, t_vec t, t_rot r, double a);
int				add_obj(t_env *e, t_obj obj);
int				add_light(t_env *e, t_lit light);


static const t_objfx	g_objfx[] = {
	{CYLINDER, "cyl", &cylinder_parse, &cylinder_line, &cylinder_norm},
	{CONE, "con", &cone_parse, &cone_line, &cone_norm},
	{SPHERE, "sph", &sphere_parse, &sphere_line, &sphere_norm},
	{PLANE, "pla", &plane_parse, &plane_line, &plane_norm},
	{LIGHT, "lit", &light_parse, NULL, NULL},
	{CAMERA, "cam", &camera_parse, NULL, NULL},
	{TYPE_END, "none", NULL, NULL, NULL}
};

t_insecres		insec(t_env *e, t_line line);
int				raytrace(t_env *e, t_line l);
int				key_hook(int key, t_env *e);
void			quit(t_env *e, char *msg);

#endif
