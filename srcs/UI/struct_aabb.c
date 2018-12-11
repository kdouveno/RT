/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_aabb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:12:33 by schaaban          #+#    #+#             */
/*   Updated: 2018/10/11 15:49:50 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtui.h"

int					aabb_col_pt(t_aabb aabb, t_v2 pt)
{
	if (pt.x >= aabb.x && pt.x < (aabb.x + aabb.w)
		&& pt.y >= aabb.y && pt.y < (aabb.y + aabb.h))
		return (1);
	return (0);
}
