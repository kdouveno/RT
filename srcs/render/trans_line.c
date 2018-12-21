/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 10:55:21 by kdouveno          #+#    #+#             */
/*   Updated: 2018/12/21 12:05:07 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_line	trans_line(t_line in, t_matrix *o)
{
	in.m = trans_pt(in.m, o);
	in.v = trans_vec(in.v, o);
	return (in);
}

t_line	rtrans_line(t_line in, t_matrix *o)
{
	in.m = rtrans_pt(in.m, o);
	in.v = rtrans_vec(in.v, o);
	return (in);
}
