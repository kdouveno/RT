/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtui.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:08:07 by schaaban          #+#    #+#             */
/*   Updated: 2019/01/24 09:48:47 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTUI_H
# define RTUI_H

# include <SDL.h>

# define UI_WIDTH				440
# define UI_HEIGHT				600

# define UI_SCROLL_SP			50

# define UI_BTN_Y				50
# define UI_BTN_SPC				25
# define UI_BTN_DOWN_Y			150

# define UI_BTN_DG_X			274
# define UI_BTN_DG_Y			28
# define UI_BTN_DG_SPC			0

typedef struct s_ui				t_ui;
typedef struct s_list_win		t_list_win;
typedef struct s_aabb			t_aabb;
typedef struct s_list_btn		t_list_btn;
typedef struct s_menu			t_menu;
typedef struct s_gui			t_gui;
typedef struct s_pbar			t_pbar;

struct				s_list_win
{
	Uint32			id;
	SDL_Window		*win;
	SDL_Surface		*render;
	int				cam;
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
	void			(*action_call)(void*, int);
	t_list_btn		*next;
};

struct				s_pbar
{
	SDL_Surface		*frame;
	SDL_Surface		*fill;
	t_vec			pos;
	double			value;
	int				shown;
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

struct				s_ui
{
	SDL_Event		event;
	t_list_win		*list_win;
	t_list_win		*focus_win;
	t_list_win		*mouse_win;
	SDL_Surface		*digits[10];
	SDL_Surface		*btn_gray;
	t_gui			gui;
	t_pbar			pbar;
	t_aabb			btn_zone;
	Uint32			id_main_win;
	pthread_t		th_pb;
	char			*file_name;
	int				local_cam_n;
	int				is_rendering;
};

#endif
