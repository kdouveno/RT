/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:41:23 by gperez            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/11/05 16:12:12 by gperez           ###   ########.fr       */
=======
/*   Updated: 2018/11/05 19:17:29 by kdouveno         ###   ########.fr       */
>>>>>>> texture
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	debug_grad(t_grad *save)
{
	if (save != NULL)
		printf("\n\033[38;5;204mGradients :\n\n");
	while (save != NULL)
	{
		printf("Translation: %f %f %f\nDirection: %f %f %f\nColor1: %x\n"
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
		printf("\n\033[38;5;208mObjects : \n\n");
	while (save != NULL)
	{
<<<<<<< HEAD
		printf("\n\033[38;5;208m\nType: %s\nTranslation: %f %f %f\nRotation: %f %f %f\n"
		"Variable: %f\nColor: %d\nDiffuse: %f\nSpecular: %f\nID: %d\n"
=======
		printf("\nType: %s\nTranslation: %f %f %f\nRotation: %f %f %f\n"
		"Variable: %f\nColor: %x\nDiffuse: %f\nSpecular: %f\nID: %d\n"
>>>>>>> texture
		"Display: %c\nLinked to %p\n",
		g_ref[save->type].name, save->t.x, save->t.y, save->t.z,
		save->dir.x, save->dir.y, save->dir.z,
		save->v1, save->mat.color.i, save->mat.diff,
		save->mat.spec, save->id, save->disp, save->grad);
		printf("\n\033[38;5;136m");
		clips = save->clips;
		while (clips != NULL)
		{
			printf("Clip : %d\n", clips->id);
			if (clips->obj != NULL)
				printf("Linked to %s:%d\n",
					g_ref[clips->obj->type].name, clips->obj->id);
			clips = clips->next;
		}
		printf("\n\033[38;5;208m");
		save = save->next;
	}
}

static void	debug_lits(t_lit *save)
{
	if (save != NULL)
		printf("\n\033[38;5;46mLights :\n\n");
	while (save != NULL)
	{
		printf("Translation: %f %f %f\nPower: %f\nColor: %x\nID: %d\n\n",
		save->t.x, save->t.y, save->t.z,
		save->power, save->color.i, save->id);
		save = save->next;
	}
}

static void	debug_cams(t_cam *save)
{
	if (save != NULL)
		printf("\n\033[38;5;31mCameras :\n\n");
	while (save != NULL)
	{
		printf("Translation: %f %f %f\nDirection: %f %f %f\n"
		"Antialiasing: %d\nID: %d\n\n",
		save->t.x, save->t.y, save->t.z,
		save->dir.x, save->dir.y, save->dir.z,
		save->data.antialia, save->id);
		save = save->next;
	}
}

void		debug_prst(t_prst *p)
{
	while (p && (p->s.cams || p->s.lits || p->s.objs || p->s.grads))
	{
		printf("\n\n\n\033[38;5;96mPRESET :\n");
		printf("Translation: %f %f %f\nDirection: %f %f %f\n",
		p->t.x, p->t.y, p->t.z, p->dir.x, p->dir.y, p->dir.z);
		debug_cams(p->s.cams);
		debug_lits(p->s.lits);
		debug_grad(p->s.grads);
		debug_objs(p->s.objs, NULL);
		p = p->next;
	}
}

void		debug(t_env *e)
{
	debug_cams(e->s.cams);
	debug_lits(e->s.lits);
	debug_grad(e->s.grads);
	debug_objs(e->s.objs, NULL);
	debug_prst(e->p);
	if (!e->s.cams && !e->s.lits && !e->s.grads && !e->s.objs && !e->p)
		printf("\033[38;5;203m%s\n", EMPTY_SCENE);
	printf("\033[0m");
}
