/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:39:43 by gperez            #+#    #+#             */
/*   Updated: 2018/12/19 18:40:09 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geo3d.h"

t_vec	get_norm_plan(t_pt a, t_pt b, t_pt c)
{
	t_vec	ab;
	t_vec	ac;

	ab = get_vector(a, b);
	ac = get_vector(a, c);
	return (cross_product(ab, ac));
}
