/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tranformation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 17:46:45 by kdouveno          #+#    #+#             */
/*   Updated: 2018/12/19 19:12:10 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_3d	trans_3d(t_3d in, t_obj *o)
{
	while (o)
	{
		in = apply(rev_3d(o->m.l.pt), in);
		in = unrot(in, o->m.rot);
		in = apply(rev_3d(o->m.t), in);
		o = (t_obj*)o->m.l.target;
	}
	return (in);
}

t_3d	rtrans3d(t_3d in, t_obj *o)
{
	rtfr_3d(t_3d &in, o);
	return (in);
}

void	rtfr_3d(t_3d *out, t_obj *o)
{
	if (o->m.l.target)
		rtfr_3d(out, o->m.l.target);
	*out = apply(rev_3d(o->m.l.pt), *out);
	*out = unrot(*out, o->m.rot);
	*out = apply(rev_3d(o->m.t), *out);
}
