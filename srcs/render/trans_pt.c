/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_pt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 10:54:04 by kdouveno          #+#    #+#             */
/*   Updated: 2018/12/21 16:52:52 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_pt	trans_pt(t_pt in, t_matrix *o)
{
	while (o)
	{
		in = apply(o->t, in);
		in = unrot(in, o->rot);
		in = vecpro(in, o->scale);
		in = apply(o->pt, in);
		o = (t_matrix*)o->l.target;
	}
	return (in);
}

static void	rtfr_pt(t_pt *out, t_matrix *o)
{
	if (o->l.target)
		rtfr_pt(out, o->l.target);
	*out = apply(rev_3d(o->pt), *out);
	*out = vecpro(*out, 1 / o->scale);
	*out = unrot(*out, o->rot);
	*out = apply(rev_3d(o->t), *out);
}

t_pt	rtrans_pt(t_pt in, t_matrix *o)
{
	rtfr_pt(&in, o);
	return (in);
}
