/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 05:03:49 by schaaban          #+#    #+#             */
/*   Updated: 2019/01/11 15:40:59 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			s_init_digits(t_env *e)
{
	int		i;
	char	*s;

	i = -1;
	if (!(s = ft_strdup("img/digit_x.bmp")))
		error(e, MALLOC_ERROR);
	while (++i < 10)
	{
		s[10] = '0' + i;
		if (!(e->ui.digits[i] = sdl_img_import(s)))
		{
			ft_strdel(&s);
			error(e, MALLOC_ERROR);
		}
		SDL_SetColorKey(e->ui.digits[i], SDL_TRUE,
			SDL_MapRGB(e->ui.digits[i]->format, 0, 0, 0));
	}
	ft_strdel(&s);
}

static void			s_init_menu_main(t_env *e)
{
	list_btn_add(e, &(e->ui.gui.menu_main->list_btn), (t_list_btn){
		sdl_img_import("img/btn_exit.bmp"),
		sdl_img_import("img/btn_exit_h.bmp"),
		sdl_img_import("img/btn_exit_c.bmp"), (t_aabb){0, 0, 0, 0},
		0, 0, -1, &b_call_exit, NULL});
	list_btn_add(e, &(e->ui.gui.menu_main->list_btn), (t_list_btn){
		sdl_img_import("img/btn_cams.bmp"),
		sdl_img_import("img/btn_cams_h.bmp"),
		sdl_img_import("img/btn_cams_c.bmp"), (t_aabb){0, 0, 0, 0},
		0, 0, -1, &b_call_menu_cam, NULL});
}

static void			s_init_menu_cam(t_env *e, int cam_count)
{
	while (cam_count > 0)
	{
		list_btn_add(e, &(e->ui.gui.menu_cam->list_btn), (t_list_btn){
			sdl_img_import("img/btn_cam.bmp"),
			sdl_img_import("img/btn_cam_h.bmp"),
			sdl_img_import("img/btn_cam_c.bmp"), (t_aabb){0, 0, 0, 0},
			0, 0, cam_count, &b_call_open_win, NULL});
		cam_count--;
	}
	list_btn_add(e, &(e->ui.gui.menu_cam->list_btn), (t_list_btn){
		sdl_img_import("img/btn_back.bmp"),
		sdl_img_import("img/btn_back_h.bmp"),
		sdl_img_import("img/btn_back_c.bmp"), (t_aabb){0, 0, 0, 0},
		0, 0, -1, &b_call_menu_main, NULL});
}

void				s_init_gui(t_env *e)
{
	if (!(e->ui.gui.menu_main = (t_menu*)ft_memalloc(sizeof(t_menu))))
		error(e, MALLOC_ERROR);
	e->ui.gui.menu_main->list_btn = NULL;
	e->ui.gui.menu_main->cam_y = 0;
	if (!(e->ui.gui.menu_cam = (t_menu*)ft_memalloc(sizeof(t_menu))))
		error(e, MALLOC_ERROR);
	e->ui.gui.menu_cam->list_btn = NULL;
	e->ui.gui.menu_cam->cam_y = 0;
	e->ui.btn_zone = (t_aabb){0, 0, UI_WIDTH, UI_HEIGHT - UI_BTN_DOWN_Y};
	s_init_menu_main(e);
	s_init_menu_cam(e, count_cams(e));
	pbar_init(e);
	e->ui.gui.actual_menu = e->ui.gui.menu_cam;
	gui_set_button_pos(e->ui.gui.menu_main);
	gui_set_button_pos(e->ui.gui.menu_cam);
}

void				rtui_init(t_env *e)
{
	char	*win_title;

	if (!(win_title = ft_strjoin("RT - ", e->ui.file_name)))
		error(e, MALLOC_ERROR);
	e->ui.is_rendering = 0;
	if (!(e->ui.btn_gray = sdl_img_import("img/btn_gray.bmp")))
		error(e, MALLOC_ERROR);
	SDL_SetColorKey(e->ui.btn_gray, SDL_TRUE,
		SDL_MapRGB(e->ui.btn_gray->format, 0, 0, 0));
	SDL_SetSurfaceBlendMode(e->ui.btn_gray, SDL_BLENDMODE_BLEND);
	SDL_SetSurfaceAlphaMod(e->ui.btn_gray, 128);
	s_init_gui(e);
	list_win_add(e, &(e->ui.list_win), (t_list_win){0,
		SDL_CreateWindow(win_title, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, UI_WIDTH, UI_HEIGHT, 0), NULL, 0, NULL});
	ft_strdel(&win_title);
	e->ui.id_main_win = SDL_GetWindowID(e->ui.list_win->win);
	e->ui.exit = 0;
	s_init_digits(e);
}
