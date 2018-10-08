/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:30:12 by gperez            #+#    #+#             */
/*   Updated: 2018/10/08 16:13:24 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include "mlx.h"
# include "geo3d.h"
# include "libft.h"
# include "gnl.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# define DIMX 900
# define DIMY 700

typedef struct			s_mlx
{
	void				*ptr;
	void				*win;
	void				*iptr;
	int					*img;
	int					imgul[3];
}						t_mlx;

typedef struct			s_wininfo
{
	int					x;
	int					y;
}						t_wininfo;

typedef struct			s_cam
{
	t_pt				t;
	t_vec				dir;
	t_vec				x;
	t_vec				y;
	t_pt				vp_ul;
	char				*id;
	struct s_cam		*next;
}						t_cam;

typedef struct			s_lit
{
	t_pt				t;
	float				power;
	t_color				color;
	char				*id;
	struct s_lit		*next;
}						t_lit;

typedef struct			s_obj
{
	int					type;
	t_pt				t;
	t_rot				r;
	double				v1;
	t_color				color;
	float				diff;
	float				spec;
	char				*id;
	char				disp;
	struct s_obj		*clips;
	struct s_obj		*deg;
	struct s_obj		*next;
}						t_obj;

typedef struct			s_scene
{
	t_obj				*objs;
	t_lit				*lits;
	t_cam				*cam;
}						t_scene;

typedef struct			s_env
{
	t_mlx				mlx;
	t_wininfo			w;
	t_scene				s;
	int					antialiasing;
}						t_env;

typedef struct			s_set
{
	double				t;
	struct s_set		*next;
}						t_set;

typedef struct			s_insecres
{
	t_obj				*obj;
	double				t;
}						t_insecres;

typedef struct			s_objfx
{
	char				name[10];
	void				(*parse)(t_env *e, int type, int fd);
}						t_objfx;

int						is_name_char(char c);
int						is_ignored(char c);
void					wrong_type(t_env *e, char *l_type, int fd, int skip);

int						get_prop(t_env *e, char *line, char **l1, char **l2);
void					parse(t_env *e, char *arg);
void					obj_parse(t_env *e, int type, int fd);
void					light_parse(t_env *e, int type, int fd);
void					cam_parse(t_env *e, int type, int fd);
void					env_parse(t_env *e, int type, int fd);
void					deg_parse(t_env *e, int type, int fd);

static const t_objfx	g_ref[] = {
	{"env", &env_parse},
	{"camera", &cam_parse},
	{"light", &light_parse},
	{"sphere", &obj_parse},
	{"cone", &obj_parse},
	{"cylinder", &obj_parse},
	{"plane", &obj_parse},
	{"pyramid", &obj_parse},
	{"torus", &obj_parse},
	{"cuboid", &obj_parse},
	{"deg", &deg_parse},
	{"", NULL}
};

void					set_camera(t_env *e, t_vec t, t_rot r, double a);
int						add_obj(t_env *e, t_obj obj);
int						add_light(t_env *e, t_lit light);

t_insecres				insec(t_env *e, t_line line);
int						raytrace(t_env *e, t_line l);
int						key_hook(int key, t_env *e);

void					error(t_env *e, char *msg);
void					quit(t_env *e, char *msg);

#endif
