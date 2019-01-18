/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_nit_lit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 16:59:38 by gperez            #+#    #+#             */
/*   Updated: 2019/01/18 17:05:10 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color				init_lit_scene(t_env *e, t_scene *s, int *nb_l)
{
	t_lit	*l;
	t_prst	*p;

	l = s->lits;
	p = s->prsts;
	while (l)
	{
		link_locs(s, l);
		check_link_loop(e, &l->m, l->m.l.target);
		l->cpt = trans_pt((t_pt){0, 0, 0}, &l->m);
		s->amb_lit_c = rgbadd(s->amb_lit_c, l->color);
		(*nb_l)++;
		while (p)
		{
			e->s.amb_lit_c = rgbadd(init_lit_scene(e, &(p->s), nb_l),
				e->s.amb_lit_c);
			p = p->next;
		}
		l = l->next;
	}
	return (s->amb_lit_c);
}

inline static int	nb_light(t_scene *s)
{
	t_lit	*l;
	int		c;

	c = 0;
	l = s->lits;
	while (l)
	{
		c++;
		l = l->next;
	}
	return (c);
}

void				init_light_auto(t_scene *s)
{
	t_lit	*l;
	int		c;

	c = nb_light(s);
	if (c == 1)
		return ;
	l = s->lits;
	while (l)
	{
		l->power = l->power / c;
		l = l->next;
	}
}
