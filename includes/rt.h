/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:30:12 by gperez            #+#    #+#             */
/*   Updated: 2018/10/22 15:22:34 by kdouveno         ###   ########.fr       */
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
# define FOV 85

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
	t_three_d			dir;
	double				r;
	t_pt				vp_ul;
	double				fov;
	int					antialia;
	int					id;
	struct s_cam		*next;
}						t_cam;

typedef struct			s_fd
{
	int					fd;
	char*				file;
}						t_fd;

typedef struct			s_lit
{
	t_pt				t;
	float				power;
	t_color				color;
	int					id;
	struct s_lit		*next;
}						t_lit;

typedef struct			s_grad
{
	t_pt				t;
	t_three_d			dir;
	int					id;
	t_color				color1;
	t_color				color2;
	struct s_grad		*next;
}						t_grad;

typedef struct			s_obj
{
	t_pt				t;
	t_three_d			dir;
	double				r;
	int					type;
	double				v1;
	t_color				color;
	float				diff;
	float				spec;
	int					id;
	char				disp;
	struct s_clip		*clips;
	t_grad				*grad;
	struct s_obj		*next;
}						t_obj;

typedef struct			s_clip
{
	int					id;
	t_obj				*obj;
	struct s_clip		*next;
}						t_clip;

typedef struct			s_scene
{
	t_obj				*objs;
	t_lit				*lits;
	t_cam				*cams;
	t_grad				*grads;
}						t_scene;

typedef struct			s_env
{
	t_mlx				mlx;
	t_wininfo			w;
	t_scene				s;
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
char					*get_name(t_env *e, char *line, int i, int *l);
void					parse(t_env *e, char *arg);
void					obj_parse(t_env *e, int type, int fd);
void					light_parse(t_env *e, int type, int fd);
void					cam_parse(t_env *e, int type, int fd);
void					env_parse(t_env *e, int type, int fd);
void					grad_parse(t_env *e, int type, int fd);
void					link_obj(t_env *e);
void					creat_clips(t_env *e, t_obj *obj, char *l2);
void					link_mat(t_env *e, t_obj *obj, char *file);
void					stock_obj(t_env *e, t_obj *obj, char *l1, char *l2);

int						check_pt(void *cam, char* l1, char *l2);
int						check_dir(void *cam, char* l1, char *l2);
int						check_rot(void *cam, char *l1, char *l2);
int						check_mat(t_env *e, t_obj *obj, char* l1, char *l2);

int						check_file_mat(const char *str);
char					*file_name(char *str);

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
	{"grad", &grad_parse},
	{"", NULL}
};

void					set_camera(t_env *e, t_vec t, t_rot r, double a);
int						add_obj(t_env *e, t_obj obj);
int						add_light(t_env *e, t_lit light);

t_insecres				insec(t_env *e, t_line line);
int						raytrace(t_env *e, t_line l);
int						key_hook(int key, t_env *e);

void					arg(t_env *e, char **argv, int argc);
void					free_env(t_env *e);
void					debug(t_env *e);
void					error(t_env *e, char *msg);

int						my_key(int key, t_env *e);
void					k_escape(t_env *e);
void					quit(t_env *e, char *msg);

#endif
