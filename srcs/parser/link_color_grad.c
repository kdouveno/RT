/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_color_grad.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:44:27 by gperez            #+#    #+#             */
/*   Updated: 2018/11/07 15:38:31 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		grad_vec_nonull(t_grad *grads, t_grad *save_g)
{
	while (save_g)
	{
		if (save_g->id == (signed)grads->color1.i && grads->b.c1 == 1)
		{
			if (save_g->b.c1 == 0)
				grads->color1.i = save_g->color1.i;
			else
				grads->color1.i = 0;
			return ;
		}
		else if (save_g->id == (signed)grads->color2.i && grads->b.c2 == 1)
		{
			if (save_g->b.c1 == 0)
				grads->color2.i = save_g->color2.i;
			else
				grads->color2.i = 0;
			return ;
		}
		save_g = save_g->next;
	}
	grads->color1.i = 0;
}

static void		grad_vec_null(t_grad *grads, t_grad *save_g)
{
	while (save_g)
	{
		if (save_g->id == (signed)grads->color1.i)
		{
			if (save_g->b.c1 == 0)
				grads->color1.i = save_g->color1.i;
			else
				grads->color1.i = 0;
			return ;
		}
		save_g = save_g->next;
	}
	grads->color1.i = 0;
}

void		link_color_grad(t_env *e)
{
	t_grad	*grads;

	grads = e->s.grads;
	while (grads)
	{
		if (grads->b.c1 == 1 && is_vec_null(grads->dir) == 1)
			grad_vec_null(grads, e->s.grads);
		else if (grads->b.c1 == 1 || grads->b.c2 == 1)
			grad_vec_nonull(grads, e->s.grads);
		grads = grads->next;
	}
}
