/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_link_color_grad.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:44:27 by gperez            #+#    #+#             */
/*   Updated: 2019/01/11 14:57:16 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		grad_vec_nonull(t_grad *grads, t_grad *save_g)
{
	while (save_g)
	{
		if (save_g->id == (signed)grads->c1.i && grads->b.c1 == 1)
		{
			if (save_g->b.c1 == 0)
				grads->c1.i = save_g->c1.i;
			else
				grads->c1.i = 0;
			return ;
		}
		else if (save_g->id == (signed)grads->c2.i && grads->b.c2 == 1)
		{
			if (save_g->b.c1 == 0)
				grads->c2.i = save_g->c2.i;
			else
				grads->c2.i = 0;
			return ;
		}
		save_g = save_g->next;
	}
	grads->c1.i = 0;
}

static void		grad_vec_null(t_grad *grads, t_grad *save_g)
{
	while (save_g)
	{
		if (save_g->id == (signed)grads->c1.i)
		{
			if (save_g->b.c1 == 0)
				grads->c1.i = save_g->c1.i;
			else
				grads->c1.i = 0;
			return ;
		}
		save_g = save_g->next;
	}
	grads->c1.i = 0;
}

void			link_color_grad(t_env *e)
{
	t_grad	*grads;

	grads = e->s.grads;
	while (grads)
	{
		if (grads->b.c1 == 1
			&& is_vec_null(get_vector(grads->m.pt, grads->m.rot)))
			grad_vec_null(grads, e->s.grads);
		else if (grads->b.c1 == 1 || grads->b.c2 == 1)
			grad_vec_nonull(grads, e->s.grads);
		grads = grads->next;
	}
}
