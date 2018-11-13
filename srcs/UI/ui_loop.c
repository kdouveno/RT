/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:15:01 by schaaban          #+#    #+#             */
/*   Updated: 2018/11/13 17:48:28 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				menu_cam(t_env *e)
{
	e->gui.actual_menu = e->gui.menu_cam;
}

void				menu_main(t_env *e)
{
	e->gui.actual_menu = e->gui.menu_main;
}

void				open_new_win(t_env *e)
{
	list_win_add(e, &(e->list_win), (t_list_win){0,
		SDL_CreateWindow("Camera", 0, 0, 600, 350, 0), NULL, NULL});
	ft_clear_screen((t_color)0xffff0000U, e->list_win);
}

void				sdl_loop(t_env *e)
{
	t_list_win	*it_list_win;

	list_btn_add(e, &(e->gui.menu_main->list_btn), (t_list_btn){
		sdl_img_import("img/btn_exit.bmp"),
		sdl_img_import("img/btn_exit_h.bmp"),
		sdl_img_import("img/btn_exit_c.bmp"), (t_aabb){0, 0, 0, 0},
		0, 0, &menu_cam, NULL});
	list_btn_add(e, &(e->gui.menu_main->list_btn), (t_list_btn){
		sdl_img_import("img/btn_cam.bmp"),
		sdl_img_import("img/btn_cam_h.bmp"),
		sdl_img_import("img/btn_cam_c.bmp"), (t_aabb){0, 0, 0, 0},
		0, 0, &menu_cam, NULL});

	list_btn_add(e, &(e->gui.menu_cam->list_btn), (t_list_btn){
		sdl_img_import("img/btn_cam.bmp"),
		sdl_img_import("img/btn_cam_h.bmp"),
		sdl_img_import("img/btn_cam_c.bmp"), (t_aabb){0, 0, 0, 0},
		0, 0, &open_new_win, NULL});
	list_btn_add(e, &(e->gui.menu_cam->list_btn), (t_list_btn){
		sdl_img_import("img/btn_cam.bmp"),
		sdl_img_import("img/btn_cam_h.bmp"),
		sdl_img_import("img/btn_cam_c.bmp"), (t_aabb){0, 0, 0, 0},
		0, 0, &open_new_win, NULL});
	list_btn_add(e, &(e->gui.menu_cam->list_btn), (t_list_btn){
		sdl_img_import("img/btn_cam.bmp"),
		sdl_img_import("img/btn_cam_h.bmp"),
		sdl_img_import("img/btn_cam_c.bmp"), (t_aabb){0, 0, 0, 0},
		0, 0, &open_new_win, NULL});
	list_btn_add(e, &(e->gui.menu_cam->list_btn), (t_list_btn){
		sdl_img_import("img/btn_cam.bmp"),
		sdl_img_import("img/btn_cam_h.bmp"),
		sdl_img_import("img/btn_cam_c.bmp"), (t_aabb){0, 0, 0, 0},
		0, 0, &open_new_win, NULL});
	list_btn_add(e, &(e->gui.menu_cam->list_btn), (t_list_btn){
		sdl_img_import("img/btn_cam.bmp"),
		sdl_img_import("img/btn_cam_h.bmp"),
		sdl_img_import("img/btn_cam_c.bmp"), (t_aabb){0, 0, 0, 0},
		0, 0, &open_new_win, NULL});
	list_btn_add(e, &(e->gui.menu_cam->list_btn), (t_list_btn){
		sdl_img_import("img/btn_cam.bmp"),
		sdl_img_import("img/btn_cam_h.bmp"),
		sdl_img_import("img/btn_cam_c.bmp"), (t_aabb){0, 0, 0, 0},
		0, 0, &open_new_win, NULL});
	list_btn_add(e, &(e->gui.menu_cam->list_btn), (t_list_btn){
		sdl_img_import("img/btn_back.bmp"),
		sdl_img_import("img/btn_back_h.bmp"),
		sdl_img_import("img/btn_back_c.bmp"), (t_aabb){0, 0, 0, 0},
		0, 0, &menu_main, NULL});

	e->gui.actual_menu = e->gui.menu_main;

	gui_set_button_pos(e->gui.menu_main);
	gui_set_button_pos(e->gui.menu_cam);
	while (!e->exit)
	{
		sdl_event_manager(e);

		list_btn_cam(e, 1);
		if (e->mouse_win)
		{
			if (e->mouse_win->id == e->id_main_win)
				list_btn_update(e, e->gui.actual_menu->list_btn, 0);
		}
		else
			list_btn_update(e, e->gui.actual_menu->list_btn, 1);

		ft_clear_screen((t_color)0xffffff00U,
			list_win_get(e->list_win, e->id_main_win));
		list_btn_draw(list_win_get(e->list_win, e->id_main_win),
			e->gui.actual_menu->list_btn);
		list_btn_cam(e, 0);

		it_list_win = e->list_win;
		while (it_list_win)
		{
			SDL_UpdateWindowSurface(it_list_win->win);
			it_list_win = it_list_win->next;
		}
	}
	quit(e, NULL);
}
