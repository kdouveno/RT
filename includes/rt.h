/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:30:12 by gperez            #+#    #+#             */
/*   Updated: 2018/11/22 12:15:25 by kdouveno         ###   ########.fr       */
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
# define SHADOW_S 0.1
# define DIMX 800
# define DIMY 800
# define FOV 85
# define THRD_CNT 1
# define REC_FILE 15
# define REC_BOUNCE 10
# define AMB_L 0.075
# define CONE 4
# define AMASK 0xFF000000U
# define RMASK 0x00FF0000U
# define GMASK 0x0000FF00U
# define BMASK 0x000000FFU

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
	t_vec				xy;
	double				fov;
	SDL_Surface			*render;
	int					ix;
	int					iy;
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
	t_rot				r;
	int					id;
	t_color				c1;
	t_color				c2;
	t_bool				b;
	struct s_grad		*next;
}						t_grad;

typedef struct			s_mat
{
	t_color				color;
	float				diff;
	float				spec;
	float				refl;
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
	double				scale;
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
	struct s_prst		*prsts;
	int					auto_l;
	t_color				amb_lit_c;
}						t_scene;

typedef struct			s_prst
{
	t_pt				t;
	t_three_d			dir;
	double				scale;
	t_scene				s;
	struct s_prst		*next;
}						t_prst;

typedef struct			s_env
{
	t_global			glb;
	t_wininfo			w;
	t_scene				s;
}						t_env;

typedef struct			s_rendering
{
	pthread_mutex_t		lock;
	t_env				*e;
	t_cam				*c;
	SDL_Surface			*s;
}						t_rendering;

/*
**	PARSER
*/

int						is_name_char(char c);
int						is_ignored(char c);
int						is_vec_null(t_vec vec);
void					wrong_type(t_env *e, char *l_type, int fd, int skip);

int						get_prop(t_env *e, char *line, char **l1, char **l2);
char					*get_name(t_env *e, char *line, int i, int *l);
void					parse(t_env *e, char *arg, t_prst *p);
void					parse_obj(t_env *e, int type, int fd, t_scene *s);
void					parse_light(t_env *e, int type, int fd, t_scene *s);
void					parse_cam(t_env *e, int type, int fd, t_scene *s);
void					parse_scene(t_env *e, int type, int fd, t_scene *s);
void					parse_grad(t_env *e, int type, int fd, t_scene *s);
void					parse_prst(t_env *e, int type, int fd, t_scene *s);
void					parse_color(t_obj *obj, char *l2, t_grad *grad, int nb);
void					creat_clips(t_env *e, t_obj *obj, char *l2);
void					stock_obj(t_env *e, t_obj *obj, char *l1, char *l2);

int						check_pt(void *cam, char* l1, char *l2);
int						check_dir(void *cam, char* l1, char *l2);
int						check_rot(void *cam, char *l1, char *l2);
int						check_value(t_obj *obj, char *l1, char *l2);
int						check_mat(t_env *e, t_obj *obj, char* l1, char *l2);

/*
**	INIT
*/

void					init(t_env *e);
void					init_objs(t_env *e, t_scene *s);
t_color					init_lit_scene(t_env *e, t_scene *s);
void					link_obj(t_env *e);
void					link_color_obj(t_env *e);
void					link_color_grad(t_env *e);
void					link_texture(t_env *e, t_obj *obj, char *file);
void					link_mat(t_env *e, t_obj *obj, char *file);

int						check_file_ext(const char *str, const char *ext);
char					*file_name(char *str);

/*
**	RENDER
*/
void					*render(void *r);
t_cam					*render_cam(t_env *e, int ncam);
t_color					raytrace(t_rendering *r, t_line l, int bounce);

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
	{"scene", &parse_scene, NULL, NULL, NULL},
	{"camera", &parse_cam, NULL, NULL, NULL},
	{"light", &parse_light, NULL, NULL, NULL},
	{"sphere", &parse_obj, &sphere_line, &sphere_norm, &sphere_isptin},
	{"cone", &parse_obj, &cone_line, &cone_norm, &cone_isptin},
	{"cylinder", &parse_obj, &cylinder_line, &cylinder_norm, &cylinder_isptin},
	{"plane", &parse_obj, &plane_line, &plane_norm, &plane_isptin},
	{"pyramid", &parse_obj, NULL, NULL, NULL},
	{"torus", &parse_obj, NULL, NULL, NULL},
	{"cuboid", &parse_obj, &cuboid_line, &cuboid_norm, &cuboid_isptin},
	{"grad", &parse_grad, NULL, NULL, NULL},
	{"preset", &parse_prst, NULL, NULL, NULL},
	{"", NULL, NULL, NULL, NULL}
};

/*
**	TOOLS
*/

int						atoi_hexa(char const *str);

void					set_camera(t_env *e, t_vec t, t_rot r, double a);
int						add_obj(t_env *e, t_obj obj);
int						add_light(t_env *e, t_lit light);

int						key_hook(int key, t_env *e);

t_polyres				solve_polynome(double a, double b, double c);
double					dist(t_pt a, t_pt b);
void					add_res(t_env *e, t_reslist **cur, t_reslist t);
void					free_res(t_reslist *list);

/*
**	ATEXIT
*/

int						arg(t_env *e, int argc, char **argv);
void					free_scene(t_scene *s);
void					debug(t_scene s, int rec);
void					error(t_env *e, const char *msg);
void					error_prst(t_prst *p, char *msg);
void					free_prst(t_prst *p);

int						my_key(int key, t_env *e);
void					k_escape(t_env *e);
void					quit(t_env *e, char *msg);

#endif
