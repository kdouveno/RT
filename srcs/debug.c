/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:41:23 by gperez            #+#    #+#             */
/*   Updated: 2018/10/15 14:19:17 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	debug_grad(t_grad *save)
{
	if (save != NULL)
		ft_putstr("\n\033[38;5;204mGradients :\n\n");
	while (save != NULL)
	{
		printf("Translation: %f %f %f\nDirection: %f %f %f\nColor1: %d\n"
		"Color2: %d\nID: %s\n\n",
		save->t.x, save->t.y, save->t.z,
		save->r.x, save->r.y, save->r.z,
		save->color1.i,save->color2.i, save->id);
		save = save->next;
	}
}

static void	debug_objs(t_obj *save)
{
	if (save != NULL)
		ft_putstr("\n\033[38;5;208mObjects :\n\n");
	while (save != NULL)
	{
		printf("Type: %s\nTranslation: %f %f %f\nRotation: %f %f %f\n"
		"Variable: %f\nColor: %d\nDiffuse: %f\nSpecular: %f\nID: %s\n"
		"Display: %c\n\n",
		g_ref[save->type].name, save->t.x, save->t.y, save->t.z,
		save->r.x, save->r.y, save->r.z,
		save->v1, save->color.i, save->diff,
		save->spec, save->id, save->disp);
		save = save->next;
	}
}

static void	debug_lits(t_lit *save)
{
	if (save != NULL)
		ft_putstr("\n\033[38;5;46mLights :\n\n");
	while (save != NULL)
	{
		printf("Translation: %f %f %f\nPower: %f\nColor: %d\nID: %s\n\n",
		save->t.x, save->t.y, save->t.z,
		save->power, save->color.i, save->id);
		save = save->next;
	}
}

static void	debug_cams(t_cam *save)
{
	if (save != NULL)
		ft_putstr("\n\033[38;5;31mCameras :\n\n");
	while (save != NULL)
	{
		printf("Translation: %f %f %f\nDirection: %f %f %f\n"
		"Antialiasing: %d\nID: %s\n\n",
		save->t.x, save->t.y, save->t.z,
		save->r.x, save->r.y, save->r.z,
		save->antialia, save->id);
		save = save->next;
	}
}

void		debug(t_env *e)
{
	t_cam	*cams;
	t_lit	*lits;
	t_grad	*grad;
	t_obj	*objs;

	cams = e->s.cams;
	lits = e->s.lits;
	grad = e->s.grads;
	objs = e->s.objs;
	debug_cams(cams);
	debug_lits(lits);
	debug_grad(grad);
	debug_objs(objs);
	ft_putstr("\033[0m");
}
