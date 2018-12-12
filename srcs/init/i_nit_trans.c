/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_nit_trans.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 14:44:45 by kdouveno          #+#    #+#             */
/*   Updated: 2018/12/12 16:37:08 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_matrix	zero_matrix()
{
	return ((t_matrix){{-1, {0, 0, 0}, NULL}, {0, 0, 0}, {0, 0, 0}, -1, -1});
}
