/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 06:49:38 by schaaban          #+#    #+#             */
/*   Updated: 2018/12/11 14:34:24 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				gui_set_button_pos(t_menu *menu)
{
	t_list_btn	*it;
	int			ch;
	int			i;

	ch = 0;
	i = 0;
	it = menu->list_btn;
	if (!it)
		return ;
	while (it)
	{
		it->aabb.x = (double)((double)UI_WIDTH * 0.5) - (it->aabb.w * 0.5);
		it->aabb.y = (double)((double)UI_BTN_Y + ((double)UI_BTN_SPC * i)) + ch;
		ch += it->aabb.h;
		it = it->next;
		i++;
	}
	it = menu->list_btn;
	while (it->next)
		it = it->next;
	menu->max_y = it->aabb.y + it->aabb.h;
}
