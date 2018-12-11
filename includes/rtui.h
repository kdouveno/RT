/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtui.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:08:07 by schaaban          #+#    #+#             */
/*   Updated: 2018/12/11 15:06:57 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTUI_H
# define RTUI_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <SDL.h>
# include "SDL_image.h"
# include "libft.h"

# define UI_WIDTH				440
# define UI_HEIGHT				600

# define UI_SCROLL_SP			50

# define UI_BTN_Y				50
# define UI_BTN_SPC				25

# define UI_BTN_DG_X			274
# define UI_BTN_DG_Y			28
# define UI_BTN_DG_SPC			0

# define RT_PI					M_PI

# define RT_SDL_RMASK			0x00ff0000
# define RT_SDL_GMASK			0x0000ff00
# define RT_SDL_BMASK			0x000000ff
# define RT_SDL_AMASK			0xff000000

# define ERR_MALLOC				0

typedef struct s_rt
					t_rt;
typedef struct s_list_win
					t_list_win;
typedef struct s_aabb
					t_aabb;
typedef struct s_list_btn
					t_list_btn;
typedef struct s_menu
					t_menu;
typedef struct s_gui
					t_gui;
typedef struct s_v3
					t_v3;
typedef struct s_v3
					t_v2;

struct				s_list_win
{
	Uint32			id;
	SDL_Window		*win;
	SDL_Surface		*render;

	t_list_win		*next;
};

struct				s_aabb
{
	double			x;
	double			y;
	double			w;
	double			h;
};

struct				s_list_btn
{
	SDL_Surface		*tex;
	SDL_Surface		*tex_hover;
	SDL_Surface		*tex_click;

	t_aabb			aabb;

	int				st_hover;
	int				st_pressing;
	int				cam_n;

	void			(*action_call)(t_rt*, int);

	t_list_btn		*next;
};

struct				s_menu
{
	t_list_btn		*list_btn;

	int				cam_y;
	int				max_y;
};

struct				s_gui
{
	t_menu			*menu_main;
	t_menu			*menu_cam;

	t_menu			*actual_menu;
};

struct				s_rt
{
	SDL_Event		event;
	SDL_Surface		*render;
	SDL_Window		*win;

	t_list_win		*list_win;
	t_list_win		*focus_win;
	t_list_win		*mouse_win;

	SDL_Surface		*digits[10];

	t_gui			gui;

	Uint32			id_main_win;
	int				exit;
};

void				button_pressed(t_rt *rt);

double				to_rad(double degrees);
double				to_deg(double radians);

void				v3_set(t_v3 *v, double newX, double newY, double newZ);
void				v3_reset(t_v3 *v);
t_v3				v3_cpy(t_v3 v);
int					v3_cmp(t_v3 v1, t_v3 v2);
void				v3_print(t_v3 v, int block);
t_v3				v3_sum(t_v3 v1, t_v3 v2);
t_v3				v3_sub(t_v3 v1, t_v3 v2);
double				v3_norm(t_v3 v);
t_v3				v3_mul(t_v3 v, double value);
t_v3				v3_div(t_v3 v, double value);
t_v3				v3_normalized(t_v3 v);
double				v3_dist(t_v3 v1, t_v3 v2);
t_v3				v3_rot_x(t_v3 v, double a);
t_v3				v3_rot_y(t_v3 v, double a);
t_v3				v3_rot_z(t_v3 v, double a);
t_v3				v3_rot(t_v3 v, double ax, double ay, double az);
double				v3_ang(t_v3 v1, t_v3 v2);

int					aabb_col_pt(t_aabb aabb, t_v2 pt);

void				list_btn_add(t_rt *rt, t_list_btn **list, t_list_btn new);
void				list_btn_del(t_list_btn *list);
void				list_btn_update(t_rt *rt, t_list_btn *list, int mouse_out);
void				list_btn_draw(t_rt *rt, t_list_win *win, t_list_btn *list);
void				list_btn_cam(t_rt *rt, int add);

void				list_win_add(t_rt *rt, t_list_win **list, t_list_win new);
void				list_win_del(t_list_win *list);
void				list_win_delone(t_list_win **list, t_list_win *el);
t_list_win			*list_win_get(t_list_win *list, Uint32 id);

void				rtui_init(t_rt *rt);

void				gui_set_button_pos(t_menu *menu);

void				b_call_menu_cam(t_rt *rt, int n);
void				b_call_menu_main(t_rt *rt, int n);
void				b_call_exit(t_rt *rt, int n);
void				b_call_open_win(t_rt *rt, int n);

void				error_handler(t_rt *rt, int error_code);
void				rt_exit(t_rt *rt);

void				sdl_loop(t_rt *rt);
void				sdl_event_manager(t_rt *rt);

void				ft_update(t_rt *rt);

SDL_Surface			*sdl_img_import(char *filename);
void				sdl_img_export(SDL_Surface *img, char *filename);
void				rt_export_screenshoot(t_rt *rt, char *filename);

void				ft_put_pixel(int x, int y, Uint32 c, t_list_win *win);
void				ft_clear_screen(Uint32 color, t_list_win *win);

#endif
