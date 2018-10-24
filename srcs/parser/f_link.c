/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_link.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 14:13:40 by gperez            #+#    #+#             */
/*   Updated: 2018/10/24 11:30:58 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		grad_vec_nonull(t_grad *grads, t_grad *save_g)
{
	while (save_g)
	{
		if (is_vec_null(save_g->dir) ==  && (save_g->id == grads->color1 ||
			save_g->id == grads->color2))
		{
			if (save_g->id == grads->color1)
				grads->color1 = save_g->color1;
			else
				grads->color2 = save_g->color1;
			return ;
		}
		else if (save_g->id == grads->color1 || save_g->id == grads->color2)
		{
			if (save_g->b.c1 == 0)
			{
				if (save_g->id == grads->color1)
					grads->color1 = save_g->color1;
				else
					grads->color2 = save_g->color1;
			}
			else
				grads->color1 = 0;
			return ;
		}
		save_g = save_g->next;
	}
	grads->color1 = 0;
}

static void		grad_vec_null(t_grad *grads, t_grad *save_g)
{
	while (save_g)
	{
		if (save_g->id == grads->color1 && is_vec_null(save_g->dir) == 1)
		{
			grads->color1 = save_g->color1;
			return ;
		}
		else if (save_g->id == grads->color1)
		{
			if (save_g->b.c1 == 0)
				grads->color1 = save_g->color1;
			else
				grads->color1 = 0;
			return ;
		}
		save_g = save_g->next;
	}
	grads->color1 = 0;
}

static void		link_grad(t_env *e)
{
	t_grad	*grads
	t_grad	*save_g;
	int		check;

	check = 0;
	grads = e->s.grads;
	while (grads)
	{
		if (grads->b.c1 == 1 && is_vec_null(grads->dir) == 1)
			grad_vec_null(grads, e->s.grads);
		else if (grads->b.c1 == 1)
			grad_vec_nonull(grads, e->s.grads);
		grads = grads->next;
	}
}

static void		link_color(t_env *e)
{
/*	t_grad	*grads;
	t_obj	*objs;

	grads = e->s.grads;
	objs = e->s.objs;
	while (objs != NULL)
	{
		if (objs->id != 0)
		{
			while (grads != NULL && objs->id != grads->id)
				grads = grads->next;
			if (grads != NULL)
				objs->grad = grads;
		}
		objs = objs->next;
		grads = e->s.grads;
	}*/

}

void	link_clips(t_env *e)
{
	t_obj	*objs;
	t_obj	*check;
	t_clip	*clips;

	objs = e->s.objs;
	while (objs != NULL)
	{
		check = e->s.objs;
		clips = objs->clips;
		while (clips != NULL)
		{
			check = e->s.objs;
			while ((check != NULL)
				&& (clips->id != check->id && -clips->id != check->id))
				check = check->next;
			if ((check != NULL)
				&& (clips->id == check->id || -clips->id == check->id))
					clips->obj = check;
			clips = clips->next;
		}
		objs = objs->next;
	}
}

void		link_obj(t_env *e)
{
	link_grad(e);
	link_clips(e);
}
