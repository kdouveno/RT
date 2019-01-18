/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 14:13:40 by gperez            #+#    #+#             */
/*   Updated: 2019/01/18 16:59:24 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_scene(t_env *e, t_scene *s)
{
	if (s->auto_l)
		init_light_auto(s);
	init_objs(e, s);
	init_cam(e, s);
	init_grad(e, s);
	if (s->prsts)
		init_scene(e, &(s->prsts->s));
}

void		init(t_env *e)
{
	int	l;

	l = 0;
	init_scene(e, &(e->s));
	if (e->glb.amb_l.i == 0)
		e->s.amb_lit_c = rgbadd(e->s.amb_lit_c, init_lit_scene(e, &(e->s), &l));
	else
	{
		init_lit_scene(e, &(e->s), &l);
		e->s.amb_lit_c = e->glb.amb_l;
	}
	if (l != 0)
	{
		e->s.amb_lit_sh.p.r = e->s.amb_lit_c.p.r / l;
		e->s.amb_lit_sh.p.g = e->s.amb_lit_c.p.g / l;
		e->s.amb_lit_sh.p.b = e->s.amb_lit_c.p.b / l;
	}
	else
		e->s.amb_lit_sh = e->s.amb_lit_c;
}
