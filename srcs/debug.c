/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:41:23 by gperez            #+#    #+#             */
/*   Updated: 2018/10/18 16:03:30 by gperez           ###   ########.fr       */
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
		"Color2: %d\nID: %d\n\n",
		save->t.x, save->t.y, save->t.z,
		save->dir.x, save->dir.y, save->dir.z,
		save->color1.i,save->color2.i, save->id);
		save = save->next;
	}
}

static void	debug_objs(t_obj *save, t_clip *clips)
{
	if (save != NULL)
		ft_putstr("\n\033[38;5;208mObjects :\n\n");
	while (save != NULL)
	{
		printf("\nType: %s\nTranslation: %f %f %f\nRotation: %f %f %f\n"
		"Variable: %f\nColor: %d\nDiffuse: %f\nSpecular: %f\nID: %d\n"
		"Display: %c\nLinked to %p\n",
		g_ref[save->type].name, save->t.x, save->t.y, save->t.z,
		save->dir.x, save->dir.y, save->dir.z,
		save->v1, save->mat.color.i, save->mat.diff,
		save->mat.spec, save->id, save->disp, save->grad);
		ft_putstr("\n\033[38;5;136m");
		clips = save->clips;
		while (clips != NULL)
		{
			printf("Clip : %d\n", clips->id);
			if (clips->obj != NULL)
				printf("Linked to %s:%d\n",
					g_ref[clips->obj->type].name, clips->obj->id);
			clips = clips->next;
		}
		ft_putstr("\n\033[38;5;208m");
		save = save->next;
	}
}

static void	debug_lits(t_lit *save)
{
	if (save != NULL)
		ft_putstr("\n\033[38;5;46mLights :\n\n");
	while (save != NULL)
	{
		printf("Translation: %f %f %f\nPower: %f\nColor: %d\nID: %d\n\n",
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
		"Antialiasing: %d\nID: %d\n\n",
		save->t.x, save->t.y, save->t.z,
		save->dir.x, save->dir.y, save->dir.z,
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
	t_clip	*clips;

	clips = NULL;
	cams = e->s.cams;
	lits = e->s.lits;
	grad = e->s.grads;
	objs = e->s.objs;
	debug_cams(cams);
	debug_lits(lits);
	debug_grad(grad);
	debug_objs(objs, clips);
	ft_putstr("\033[0m");
}
