/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 05:03:49 by schaaban          #+#    #+#             */
/*   Updated: 2018/12/11 14:27:27 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtui.h"

static void			s_init_digits(t_rt *rt)
{
	int		i;
	char	*s;

	i = -1;
	if (!(s = ft_strdup("img/digit_x.bmp")))
		error_handler(rt, ERR_MALLOC);
	while (++i < 10)
	{
		s[10] = '0' + i;
		if (!(rt->digits[i] = sdl_img_import(s)))
		{
			ft_strdel(&s);
			error_handler(rt, ERR_MALLOC);
		}
		SDL_SetColorKey(rt->digits[i], SDL_TRUE, 0);
	}
	ft_strdel(&s);
}

static void			s_init_menu_main(t_rt *rt)
{
	list_btn_add(rt, &(rt->gui.menu_main->list_btn), (t_list_btn){
		sdl_img_import("img/btn_exit.bmp"),
		sdl_img_import("img/btn_exit_h.bmp"),
		sdl_img_import("img/btn_exit_c.bmp"), (t_aabb){0, 0, 0, 0},
		0, 0, -1, &b_call_exit, NULL});
	list_btn_add(rt, &(rt->gui.menu_main->list_btn), (t_list_btn){
		sdl_img_import("img/btn_cams.bmp"),
		sdl_img_import("img/btn_cams_h.bmp"),
		sdl_img_import("img/btn_cams_c.bmp"), (t_aabb){0, 0, 0, 0},
		0, 0, -1, &b_call_menu_cam, NULL});
}

static void			s_init_menu_cam(t_rt *rt, int cam_count)
{
	while (cam_count > 0)
	{
		list_btn_add(rt, &(rt->gui.menu_cam->list_btn), (t_list_btn){
			sdl_img_import("img/btn_cam.bmp"),
			sdl_img_import("img/btn_cam_h.bmp"),
			sdl_img_import("img/btn_cam_c.bmp"), (t_aabb){0, 0, 0, 0},
			0, 0, cam_count, &b_call_open_win, NULL});
		cam_count--;
	}
	list_btn_add(rt, &(rt->gui.menu_cam->list_btn), (t_list_btn){
		sdl_img_import("img/btn_back.bmp"),
		sdl_img_import("img/btn_back_h.bmp"),
		sdl_img_import("img/btn_back_c.bmp"), (t_aabb){0, 0, 0, 0},
		0, 0, -1, &b_call_menu_main, NULL});
}

void				rtui_init(t_rt *rt)
{
	if (!(rt->gui.menu_main = (t_menu*)ft_memalloc(sizeof(t_menu))))
		error_handler(rt, ERR_MALLOC);
	rt->gui.menu_main->list_btn = NULL;
	rt->gui.menu_main->cam_y = 0;
	if (!(rt->gui.menu_cam = (t_menu*)ft_memalloc(sizeof(t_menu))))
		error_handler(rt, ERR_MALLOC);
	rt->gui.menu_cam->list_btn = NULL;
	rt->gui.menu_cam->cam_y = 0;
	list_win_add(rt, &(rt->list_win), (t_list_win){0,
		SDL_CreateWindow("RT - UI", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, UI_WIDTH, UI_HEIGHT, 0), NULL, NULL});
	rt->id_main_win = SDL_GetWindowID(rt->list_win->win);
	rt->exit = 0;
	s_init_digits(rt);
	s_init_menu_main(rt);
	s_init_menu_cam(rt, 8);
	rt->gui.actual_menu = rt->gui.menu_main;
	gui_set_button_pos(rt->gui.menu_main);
	gui_set_button_pos(rt->gui.menu_cam);
}
