/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:30:12 by gperez            #+#    #+#             */
/*   Updated: 2019/01/24 09:53:08 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include "geo3d.h"
# include "libft.h"
# include "gnl.h"
# include "msgs.h"
# include "rtui.h"
# include <pthread.h>
# include <fcntl.h>
# define PRE 0.000000001
# define OFFSET 100000000
# define SHADOW_REC 3
# define SHADOW_RAY 6
# define SHADOW_C 0.16666
# define DIMX 800
# define DIMY 800
# define FOV 85
# define THRD_CNT 1
# define REC_FILE 15
# define REC_BOUNCE 10
# define AMB_L 0.15
# define CONE 4
# define AAA_THRESH 35
# define BMP_LEVEL 1.5
# define AMASK 0xFF000000U
# define RMASK 0x00FF0000U
# define GMASK 0x0000FF00U
# define BMASK 0x000000FFU

typedef struct			s_global
{
	int					d;
	int					rec_lim_file;
	int					rec_nb_file;
	int					thread_count;
	int					quit_signal;
	t_color				amb_l;
}						t_global;

typedef struct			s_wininfo
{
	int					x;
	int					y;
}						t_wininfo;

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

typedef struct			s_mat
{
	t_color				color;
	float				diff;
	float				spec;
	float				refl;
	float				tr;
	float				n;
	float				offx;
	float				offy;
	float				b_lvl;
	SDL_Surface			*txt;
	SDL_Surface			*txt_bm;
}						t_mat;

typedef struct			s_objlist
{
	struct s_obj		*obj;
	struct s_objlist	*next;
}						t_objlist;

typedef struct			s_link
{
	int					id;
	struct s_matrix		*target;
}						t_link;

typedef struct			s_matrix
{
	t_link				l;
	t_pt				pt;
	t_vec				t;
	t_3d				rot;
	double				r;
	double				scale;
}						t_matrix;

typedef struct			s_cam_render
{
	t_pt				vp_ul;
	t_pt				pt_ul;
	t_vec				x;
	t_vec				y;
	t_vec				xy;
	double				fov;
	SDL_Surface			*render;
	int					ix;
	int					iy;
	int					dimx;
	int					dimy;
	int					ssaa;
	int					aaa;
	int					para;
	char				filter;
}						t_cam_render;

typedef struct			s_lit
{
	struct s_lit		*next;
	t_matrix			m;
	int					id;
	double				power;
	double				radius;
	t_pt				cpt;
	t_color				color;
	t_bool				b;
}						t_lit;

typedef struct			s_grad
{
	struct s_grad		*next;
	t_matrix			m;
	int					id;
	t_3d				r;
	t_pt				cpt;
	t_color				c1;
	t_color				c2;
	t_bool				b;
}						t_grad;

typedef struct			s_cam
{
	struct s_cam		*next;
	t_matrix			m;
	int					id;
	t_cam_render		data;
}						t_cam;

typedef struct			s_obj
{
	struct s_obj		*next;
	t_matrix			m;
	int					id;
	int					type;
	double				v[4];
	t_mat				mat;
	t_bool				b;
	struct s_clip		*clips;
	t_objlist			*clipping;
	t_grad				*grad;
}						t_obj;

typedef struct			s_ri
{
	struct s_ri			*next;
	t_obj				*o;
	t_obj				*co;
	float				n;
	char				c;
}						t_ri;

typedef struct			s_reslist
{
	t_obj				*o;
	t_obj				*co;
	t_pt				pt;
	t_vec				n;
	t_vec				tn;
	t_vec				cam;
	t_vec				pert;
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
	t_3d				dir;
	double				scale;
	t_scene				s;
	struct s_prst		*next;
}						t_prst;

typedef struct			s_env
{
	t_ui				ui;
	t_global			glb;
	t_wininfo			w;
	t_scene				s;
}						t_env;

typedef struct			s_rendering
{
	pthread_mutex_t		lock;
	t_env				*e;
	t_cam				*c;
}						t_rendering;

/*
**	UI
*/

int						count_cams(t_env *e);

void					button_pressed(t_env *e);

int						aabb_col_pt(t_aabb aabb, t_vec pt);

void					pbar_init(t_env *e);
void					pbar_update(t_env *e);
void					pbar_draw(t_env *e);

void					list_btn_add(t_env *e, t_list_btn **list,
	t_list_btn new);
void					list_btn_del(t_list_btn *list);
void					list_btn_update(t_env *e, t_list_btn *list,
	int mouse_out);
void					list_btn_draw(t_env *e, t_list_win *win,
	t_list_btn *list);
void					list_btn_cam(t_env *e, int add);

void					list_win_add(t_env *e, t_list_win **list,
	t_list_win new);
void					list_win_del(t_list_win *list);
void					list_win_delone(t_list_win **list, t_list_win *el);
t_list_win				*list_win_get(t_list_win *list, Uint32 id);

void					rtui_init(t_env *e);

void					gui_set_button_pos(t_menu *menu);

void					b_call_menu_cam(void *e, int n);
void					b_call_menu_main(void *e, int n);
void					b_call_exit(void *e, int n);
void					b_call_open_win(void *e, int n);

void					rt_exit(t_env *e);

void					sdl_loop(t_env *e);
void					sdl_event_manager(t_env *e);
void					ft_update(t_env *e);
SDL_Surface				*sdl_img_import(char *filename);
void					sdl_img_export(SDL_Surface *img, char *filename);
void					rt_export_screenshoot(t_env *e, t_list_win *win);
void					ft_put_pixel(int x, int y, Uint32 c, t_list_win *win);
void					ft_clear_screen(Uint32 color, t_list_win *win);

/*
**	PARSER
*/

double					get_coef(double nb);
int						is_name_char(char c);
int						is_ignored(char c);
int						is_vec_null(t_vec vec);
int						is_alia(int nb);
void					wrong_type(t_env *e, char *l_type, int fd, int skip);
t_matrix				zero_matrix();
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
int						parse_3d(t_env *e, t_pt *pt, char *l2);
int						check_pt(void *cam, char *l1, char *l2);
int						check_dir(void *cam, char *l1, char *l2);
int						check_rot(void *cam, char *l1, char *l2);
int						check_value(t_obj *obj, char *l1, char *l2);
int						check_mat(t_env *e, t_obj *obj, char *l1, char *l2);
int						check_loc(t_env *e, void *obj, char *l1, char *l2);

/*
**	INIT
*/

void					init(t_env *e);
void					init_objs(t_env *e, t_scene *s);
t_color					init_lit_scene(t_env *e, t_scene *s, int *nb_l);
void					init_light_auto(t_scene *s);
void					check_link_loop(t_env *e, t_matrix *o, t_matrix *obj);
void					check_clip_loop(t_env *e, t_obj *o, t_obj *original,
	int i);
void					link_obj(t_env *e);
void					init_cam(t_env *e, t_scene *s);
void					init_grad(t_env *e, t_scene *s);
void					link_color_obj(t_env *e);
void					link_color_grad(t_env *e);
void					link_texture(t_env *e, t_obj *obj, char *file,
	char type);
void					link_locs(t_scene *s, void *o);
void					link_mat(t_env *e, t_obj *obj, char *file);
int						check_file_ext(const char *str, const char *ext);
char					*file_name(char *str);

/*
**	RENDER
*/

void					*render(void *r);
t_cam					*render_cam(t_env *e, int ncam);
t_color					raytrace(t_rendering *r, t_line l, int bounce, t_ri ri);
void					aaa(t_rendering *r);
t_color					rec_raytrace(t_rendering *r, t_line l, int m);

t_color					phong(t_lit l, t_reslist *res, t_color lc);
t_color					catch_light(t_rendering *r, t_lit *l, t_reslist *res);
t_color					get_pt_color(t_obj obj, t_pt pt, t_vec *pert);
t_color					texture_color(t_obj obj, t_pt pt, t_vec *pert,
	SDL_Surface *txt);
t_color					spherical_texture(t_obj obj, t_pt pt, t_vec *pert,
	SDL_Surface *txt);
t_color					cylinder_texture(t_obj obj, t_pt pt, t_vec *pert,
	SDL_Surface *txt);
t_color					plane_texture(t_obj obj, t_pt pt, t_vec *pert,
	SDL_Surface *txt);
void					offset_txt(t_obj obj, double *x, double *y,
	SDL_Surface *txt);
t_vec					perturbation(double x, double y, SDL_Surface *txt,
	t_obj obj);
t_color					get_text_color(int x, int y, SDL_Surface *txt,
	char *pixels);
t_color					filter(t_rendering *r, t_color p_color);
t_color					soft_shadow2(t_rendering *r, t_reslist *res, t_lit l,
	int rec);
t_color					soft_shadow(t_rendering *r, t_reslist *res, t_lit l,
	int rec);
t_color					perlin_noise(t_pt pt);
t_reslist				intersec(t_rendering *r, t_line line);
t_color					refraction(t_rendering *r, t_reslist res, int bounce,
	t_ri *ri);
t_line					trans_line(t_line in, t_matrix *o);
t_line					rtrans_line(t_line in, t_matrix *o);
t_pt					trans_pt(t_pt in, t_matrix *o);
t_pt					rtrans_pt(t_pt in, t_matrix *o);
t_vec					trans_vec(t_vec in, t_matrix *o);
t_vec					rtrans_vec(t_vec in, t_matrix *o);
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
t_vec					sphere_norm(t_pt pt, t_obj obj);
t_vec					cone_norm(t_pt pt, t_obj obj);
t_vec					cylinder_norm(t_pt pt, t_obj obj);
t_vec					plane_norm(t_pt pt, t_obj obj);
t_vec					cuboid_norm(t_pt pt, t_obj obj);
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
	t_vec				(*norm)(t_pt pt, t_obj obj);
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
	{"anchor", &parse_obj, NULL, NULL, NULL},
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
t_reslist				blank_reslist(t_obj *o, double res);
void					ft_putint(char *str, int d);

/*
**	ATEXIT
*/

int						arg(t_env *e, int argc, char **argv);
void					free_scene(t_scene *s);
void					free_obj(t_obj *obj);
void					error(t_env *e, const char *msg);
void					error_prst(t_prst *p, char *msg);
void					free_prst(t_prst *p);
void					quit(t_env *e, char *msg);

#endif
