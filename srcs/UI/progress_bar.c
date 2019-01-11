/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 18:52:27 by schaaban          #+#    #+#             */
/*   Updated: 2019/01/11 14:31:04 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				pbar_init(t_env *e)
{
	if (!(e->ui.pbar.frame = sdl_img_import("img/pb_frame.bmp")))
		error(e, MALLOC_ERROR);
	if (!(e->ui.pbar.fill = sdl_img_import("img/pb_fill.bmp")))
	{
		if (e->ui.pbar.frame)
			SDL_FreeSurface(e->ui.pbar.frame);
		error(e, MALLOC_ERROR);
	}
	SDL_SetColorKey(e->ui.pbar.fill, SDL_TRUE,
		SDL_MapRGB(e->ui.pbar.fill->format, 0, 0, 0));
	e->ui.pbar.value = 1;
	e->ui.pbar.shown = 0;
	e->ui.pbar.pos = (t_vec){UI_WIDTH / 2, UI_HEIGHT - (UI_BTN_DOWN_Y / 2), 0};
}

void				pbar_update(t_env *e)
{
	if (e->ui.pbar.value < 0)
		e->ui.pbar.value = 0;
	if (e->ui.pbar.value >= 1)
		e->ui.pbar.value = 0;
	e->ui.pbar.shown = (e->ui.pbar.value == 0) ? 0 : 1;
}

static void			s_draw_number(t_env *e, t_list_win *win,
	t_vec pos, int value)
{
	if (value < 10)
	{
		SDL_BlitSurface(
			e->ui.digits[(int)(value)], NULL, win->render, &((SDL_Rect){pos.x
			- (e->ui.digits[(int)(value)]->w / 2), pos.y
			- (e->ui.digits[(int)(value)]->h / 2),
			e->ui.digits[(int)(value)]->w, e->ui.digits[(int)(value)]->h}));
	}
	else if (value >= 10 && value <= 99)
	{
		SDL_BlitSurface(
			e->ui.digits[(int)(value / 10)], NULL, win->render, &((SDL_Rect){
				pos.x - (e->ui.digits[(int)(value / 10)]->w) - (UI_BTN_DG_SPC
				/ 2), pos.y - (e->ui.digits[(int)(value / 10)]->h / 2),
				e->ui.digits[(int)(value) / 10]->w,
				e->ui.digits[(int)(value) / 10]->h}));
		SDL_BlitSurface(
			e->ui.digits[(int)(value % 10)], NULL, win->render, &((SDL_Rect){
				pos.x + (UI_BTN_DG_SPC / 2), pos.y
				- (e->ui.digits[(int)(value % 10)]->h / 2),
				e->ui.digits[(int)(value % 10)]->w,
				e->ui.digits[(int)(value % 10)]->h}));
	}
}

void				pbar_draw(t_env *e)
{
	SDL_FillRect(list_win_get(e->ui.list_win, e->ui.id_main_win)->render,
		&((SDL_Rect){0, UI_HEIGHT - UI_BTN_DOWN_Y,
		UI_WIDTH, UI_BTN_DOWN_Y}), 0xff3f3f3f);
	if (!e->ui.pbar.shown)
		return ;
	SDL_BlitSurface(e->ui.pbar.frame, NULL, list_win_get(e->ui.list_win,
		e->ui.id_main_win)->render, &((SDL_Rect){e->ui.pbar.pos.x
		- (e->ui.pbar.frame->w / 2), e->ui.pbar.pos.y
		- (e->ui.pbar.frame->h / 2),
		e->ui.pbar.frame->w, e->ui.pbar.frame->h}));
	SDL_BlitSurface(e->ui.pbar.fill, &((SDL_Rect){0, 0, (e->ui.pbar.fill->w
		- 19) * e->ui.pbar.value, e->ui.pbar.fill->h}),
		list_win_get(e->ui.list_win, e->ui.id_main_win)->render,
		&((SDL_Rect){e->ui.pbar.pos.x
		- (e->ui.pbar.frame->w / 2), e->ui.pbar.pos.y
		- (e->ui.pbar.frame->h / 2),
		e->ui.pbar.fill->w, e->ui.pbar.fill->h}));
	s_draw_number(e, list_win_get(e->ui.list_win, e->ui.id_main_win),
		(t_vec){e->ui.pbar.pos.x, e->ui.pbar.pos.y + 9,
		0}, floor(e->ui.pbar.value * 100));
}
