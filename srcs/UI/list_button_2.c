/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_button_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 04:13:24 by schaaban          #+#    #+#             */
/*   Updated: 2018/12/10 17:53:30 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			s_btn_update(t_env *e, t_list_btn *button)
{
	t_v2	mouse_v2;
	int		mpos_i[2];

	SDL_GetMouseState(&mpos_i[0], &mpos_i[1]);
	mouse_v2 = (t_v2){(double)mpos_i[0], (double)mpos_i[1], 0};
	if (aabb_col_pt(button->aabb, mouse_v2) && e->ui.mouse_win)
	{
		button->st_hover = 1;
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
			button->st_pressing = 1;
		else
		{
			if (button->st_pressing)
			{
				button->st_pressing = 0;
				(button->action_call)(rt, button->cam_n);
			}
		}
	}
	else
	{
		button->st_pressing = 0;
		button->st_hover = 0;
	}
}

void				list_btn_update(t_env *e, t_list_btn *list, int mouse_out)
{
	t_list_btn	*it;

	it = list;
	while (it)
	{
		if (!mouse_out)
			s_btn_update(rt, it);
		else
		{
			if (!(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)))
				it->st_pressing = 0;
			it->st_hover = 0;
		}
		it = it->next;
	}
}

static void			s_draw_digits(t_env *e, t_list_win *win, t_list_btn *btn)
{
	t_v3	click;

	click = (btn->st_pressing) ? (t_v3){9, -9, 0} : (t_v3){0, 0, 0};
	if (btn->cam_n < 10)
	{
		SDL_BlitSurface(e->ui.digits[(int)(btn->cam_n)], NULL, win->render,
			&((SDL_Rect){btn->aabb.x + UI_BTN_DG_X + (UI_BTN_DG_SPC / 2)
			+ e->ui.digits[(int)(btn->cam_n)]->w
			- (e->ui.digits[(int)(btn->cam_n)]->w / 2) + click.x,
			btn->aabb.y + UI_BTN_DG_Y + click.y, btn->aabb.w, btn->aabb.h}));
	}
	else
	{
		SDL_BlitSurface(e->ui.digits[(int)(btn->cam_n / 10)], NULL, win->render,
			&((SDL_Rect){btn->aabb.x + UI_BTN_DG_X + click.x,
			btn->aabb.y + UI_BTN_DG_Y + click.y, btn->aabb.w, btn->aabb.h}));
		SDL_BlitSurface(e->ui.digits[(int)(btn->cam_n % 10)], NULL, win->render,
			&((SDL_Rect){btn->aabb.x + UI_BTN_DG_X + UI_BTN_DG_SPC
			+ e->ui.digits[(int)(btn->cam_n % 10)]->w + click.x,
			btn->aabb.y + UI_BTN_DG_Y + click.y, btn->aabb.w, btn->aabb.h}));
	}
}

void				list_btn_draw(t_env *e, t_list_win *win, t_list_btn *list)
{
	t_list_btn	*it;

	it = list;
	while (it)
	{
		SDL_BlitSurface(it->tex, NULL, win->render, &((SDL_Rect){it->aabb.x,
			it->aabb.y, it->aabb.w, it->aabb.h}));
		if (it->st_hover)
		{
			if (it->tex_hover)
				SDL_BlitSurface(it->tex_hover, NULL, win->render, &((SDL_Rect)
					{it->aabb.x, it->aabb.y, it->aabb.w, it->aabb.h}));
		}
		if (it->st_pressing)
		{
			if (it->tex_click)
				SDL_BlitSurface(it->tex_click, NULL, win->render, &((SDL_Rect)
					{it->aabb.x, it->aabb.y, it->aabb.w, it->aabb.h}));
		}
		if (it->cam_n >= 0)
			s_draw_digits(rt, win, it);
		it = it->next;
	}
}
