/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 17:46:45 by kdouveno          #+#    #+#             */
/*   Updated: 2018/12/21 16:24:55 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	trans_vec(t_vec in, t_matrix *o)
{
	while (o)
	{
		in = rot(in, o->rot);
		in = vecpro(in, o->scale);
		o = (t_matrix*)o->l.target;
	}
	return (in);
}

void	rtfr_vec(t_vec *out, t_matrix *o)
{
	if (o->l.target)
		rtfr_vec(out, o->l.target);
	*out = unrot(*out, o->rot);
	*out = vecpro(*out, 1 / o->scale);
}

t_vec	rtrans_vec(t_vec in, t_matrix *o)
{
	rtfr_vec(&in, o);
	return (in);
}
