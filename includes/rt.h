/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:30:12 by gperez            #+#    #+#             */
/*   Updated: 2018/11/12 16:26:31 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include "mlx.h"
# include "geo3d.h"
# include "libft.h"
# include "gnl.h"
# include "X.h"
# include <stdlib.h>
# include "SDL.h"
# include <pthread.h>
# include <stdio.h>
# include <fcntl.h>
# define PRE 0.00000001
# define DIMX 900
# define DIMY 700
# define FOV 85
# define THRD_CNT 1
# define REC_FILE 15
# define AMB_L 0.075
# define CONE 4
# define AMASK 0xFF000000U
# define RMASK 0xFF0000U
# define GMASK 0xFF00U
# define BMASK 0xFFU
typedef struct			s_global
{
	SDL_Window			*win;
	int					rec_lim_file;
	int					rec_nb_file;
	int					thread_count;
}						t_global;

typedef struct			s_wininfo
{
	int					x;
	int					y;
}						t_wininfo;

typedef struct			s_cam_render
{
	t_pt				vp_ul;
	t_vec				x;
	t_vec				y;
	double				fov;
	SDL_Surface			*render;
	int					ix;
	int					iy;
	int					xmax;
	int					ymax;
	int					dimx;
	int					dimy;
	int					antialia;
}						t_cam_render;

typedef struct			s_cam
{
	t_pt				t;
	t_three_d			dir;
	double				r;
	int					id;
	t_cam_render		data;
	struct s_cam		*next;
}						t_cam;

typedef struct			s_fd
{
	int					fd;
	char				*file;
}						t_fd;

typedef struct			s_bool
{
	unsigned char		c1 : 1;
	unsigned char		c2 : 1;
	unsigned char		clip : 1;
	unsigned char		clipr : 1;
}						t_bool;

typedef struct			s_lit
{
	t_pt				t;
	float				power;
	t_color				color;
	t_bool				b;
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
	t_bool				b;
	struct s_grad		*next;
}						t_grad;

typedef struct			s_mat
{
	t_color				color;
	float				diff;
	float				spec;
	SDL_Surface			*txt;
}						t_mat;

typedef struct			s_objlist
{
	struct s_obj		*obj;
	struct s_objlist	*next;
}						t_objlist;

typedef struct			s_obj
{
	t_pt				t;
	t_three_d			dir;
	double				r;
	int					type;
	double				v[4];
	t_mat				mat;
	t_bool				b;
	int					id;
	struct s_clip		*clips;
	t_objlist			*clipping;
	t_grad				*grad;
	struct s_obj		*next;
}						t_obj;

typedef struct			s_reslist
{
	t_obj				*o;
	t_pt				pt;
	t_vec				n;
	t_vec				cam;
	double				t;
	struct s_reslist	*next;
}						t_reslist;

typedef struct			s_set
{
	double				t;
	struct s_set		*next;
}						t_set;

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
	t_color				amb_lit_c;
}						t_scene;

typedef struct			s_prst
{
	t_pt				t;
	t_three_d			dir;
	t_scene				s;
	struct s_prst		*next;
}						t_prst;

typedef struct			s_env
{
	t_global			glb;
	t_wininfo			w;
	t_scene				s;
	t_prst				*p;
}						t_env;

typedef struct			s_rendering
{
	pthread_mutex_t		lock;
	t_env				*e;
	t_cam				*c;
	SDL_Surface			*s;
}						t_rendering;

int						is_name_char(char c);
int						is_ignored(char c);
int						is_vec_null(t_vec vec);
void					wrong_type(t_env *e, char *l_type, int fd, int skip);

int						get_prop(t_env *e, char *line, char **l1, char **l2);
char					*get_name(t_env *e, char *line, int i, int *l);
void					parse(t_env *e, char *arg, t_prst *p);
void					obj_parse(t_env *e, int type, int fd, t_scene *s);
void					light_parse(t_env *e, int type, int fd, t_scene *s);
void					cam_parse(t_env *e, int type, int fd, t_scene *s);
void					env_parse(t_env *e, int type, int fd, t_scene *s);
void					grad_parse(t_env *e, int type, int fd, t_scene *s);
void					prst_parse(t_env *e, int type, int fd, t_scene *s);
void					parse_color(t_obj *obj, char *l2, t_grad *grad, int nb);
void					creat_clips(t_env *e, t_obj *obj, char *l2);
void					stock_obj(t_env *e, t_obj *obj, char *l1, char *l2);

int						check_pt(void *cam, char* l1, char *l2);
int						check_dir(void *cam, char* l1, char *l2);
int						check_rot(void *cam, char *l1, char *l2);
int						check_value(t_obj *obj, char *l1, char *l2);
int						check_mat(t_env *e, t_obj *obj, char* l1, char *l2);

void					*render(void *r);
t_cam					*render_cam(t_env *e, int ncam);

void					init(t_env *e);
void					init_objs(t_env *e);
void					init_cam(t_env *e);
t_color					init_lit_scene(t_scene *s);
void					link_obj(t_env *e);
void					link_color_obj(t_env *e);
void					link_color_grad(t_env *e);
void					link_texture(t_env *e, t_obj *obj, char *file);
void					link_mat(t_env *e, t_obj *obj, char *file);

int						check_file_ext(const char *str, const char *ext);
char					*file_name(char *str);

void					sphere_line(t_env *e, t_line d, t_obj *o,
	t_reslist **rlist);
void					cone_line(t_env *e, t_line d, t_obj *o,
	t_reslist **rlist);
void					cylinder_line(t_env *e, t_line d, t_obj *o,
	t_reslist **rlist);
void					plane_line(t_env *e, t_line d, t_obj *o,
	t_reslist **rlist);
void					cuboid_line(t_env *e, t_line d, t_obj *o,
	t_reslist **rlist);

t_vec					sphere_norm(t_pt pt, t_obj obj, t_vec v);
t_vec					cone_norm(t_pt pt, t_obj obj, t_vec v);
t_vec					cylinder_norm(t_pt pt, t_obj obj, t_vec v);
t_vec					plane_norm(t_pt pt, t_obj obj, t_vec v);
t_vec					cuboid_norm(t_pt pt, t_obj obj, t_vec v);

int						sphere_isptin(t_pt pt, t_obj o);
int						cylinder_isptin(t_pt pt, t_obj o);
int						cone_isptin(t_pt pt, t_obj o);
int						plane_isptin(t_pt pt, t_obj o);
int						cuboid_isptin(t_pt pt, t_obj o);

double					get_norm(t_vec a);

typedef struct			s_objfx
{
	char				name[10];
	void				(*parse)(t_env *e, int type, int fd, t_scene *s);
	void				(*intersec)(t_env *e, t_line d, t_obj *o,
		t_reslist **rlist);
	t_vec				(*norm)(t_pt pt, t_obj obj, t_vec v);
	int					(*isptin)(t_pt pt, t_obj o);
}						t_objfx;

static const t_objfx	g_ref[] = {
	{"env", &env_parse, NULL, NULL, NULL},
	{"camera", &cam_parse, NULL, NULL, NULL},
	{"light", &light_parse, NULL, NULL, NULL},
	{"sphere", &obj_parse, &sphere_line, &sphere_norm, &sphere_isptin},
	{"cone", &obj_parse, &cone_line, &cone_norm, &cone_isptin},
	{"cylinder", &obj_parse, &cylinder_line, &cylinder_norm, &cylinder_isptin},
	{"plane", &obj_parse, &plane_line, &plane_norm, &plane_isptin},
	{"pyramid", &obj_parse, NULL, NULL, NULL},
	{"torus", &obj_parse, NULL, NULL, NULL},
	{"cuboid", &obj_parse, &cuboid_line, &cuboid_norm, &cuboid_isptin},
	{"grad", &grad_parse, NULL, NULL, NULL},
	{"preset", &prst_parse, NULL, NULL, NULL},
	{"", NULL, NULL, NULL, NULL}
};

typedef struct			s_char_int
{
	char				hexa;
	int					n;
}						t_char_int;


static const			t_char_int	g_hexa[] = {
	{'0', 0},
	{'1', 1},
	{'2', 2},
	{'3', 3},
	{'4', 4},
	{'5', 5},
	{'6', 6},
	{'7', 7},
	{'8', 8},
	{'9', 9},
	{'A', 10},
	{'B', 11},
	{'C', 12},
	{'D', 13},
	{'E', 14},
	{'F', 15},
	{'\0', 0}
};

void					set_camera(t_env *e, t_vec t, t_rot r, double a);
int						add_obj(t_env *e, t_obj obj);
int						add_light(t_env *e, t_lit light);

t_color					raytrace(t_rendering *r, t_line l);
int						key_hook(int key, t_env *e);

int						atoi_hexa(char const *str);
t_polyres				solve_polynome(double a, double b, double c);
double					dist(t_pt a, t_pt b);
void					add_res(t_env *e, t_reslist **cur, t_reslist t);
void					free_res(t_reslist *list);

void					arg(t_env *e, int argc, char **argv);
void					free_scene(t_scene *s);
void					debug(t_env *e);
void					error(t_env *e, const char *msg);
void					error_prst(t_prst *p, char *msg);
void					free_prst(t_prst *p);

int						my_key(int key, t_env *e);
void					k_escape(t_env *e);
void					quit(t_env *e, char *msg);

#endif
