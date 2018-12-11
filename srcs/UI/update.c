/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:44:37 by schaaban          #+#    #+#             */
/*   Updated: 2018/12/10 05:26:10 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtui.h"

void				ft_update(t_env *e)
{
	list_btn_cam(rt, 1);
	if (rt->mouse_win)
	{
		if (rt->mouse_win->id == rt->id_main_win)
			list_btn_update(rt, rt->gui.actual_menu->list_btn, 0);
	}
	else
		list_btn_update(rt, rt->gui.actual_menu->list_btn, 1);
}
