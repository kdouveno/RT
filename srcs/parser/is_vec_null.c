/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_vec_null.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 17:40:03 by gperez            #+#    #+#             */
/*   Updated: 2018/10/23 17:41:14 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	is_vec_null(t_vec vec)
{
	return (vec.x == 0 && vec.y == 0 && vec.z == 0);
}
