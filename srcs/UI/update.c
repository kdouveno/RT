/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:44:37 by schaaban          #+#    #+#             */
/*   Updated: 2019/01/11 13:03:18 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				ft_update(t_env *e)
{
	list_btn_cam(e, 1);
	if (e->ui.mouse_win)
	{
		if (e->ui.mouse_win->id == e->ui.id_main_win)
			list_btn_update(e, e->ui.gui.actual_menu->list_btn, 0);
		else
			list_btn_update(e, e->ui.gui.actual_menu->list_btn, 1);
	}
	else
		list_btn_update(e, e->ui.gui.actual_menu->list_btn, 1);
	pbar_update(e);
}
