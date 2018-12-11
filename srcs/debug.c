/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:41:23 by gperez            #+#    #+#             */
/*   Updated: 2018/11/21 18:06:46 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	debug_grad(t_grad *save)
{
	if (save != NULL)
		printf("\n\033[38;5;204mGradients :\n\n");
	while (save != NULL)
	{
		printf("Translation: %f %f %f\nDirection: %f %f %f\nColor1: %06x\n"
		"Color2: %06x\nID: %d\n\n",
		save->t.x, save->t.y, save->t.z,
		save->dir.x, save->dir.y, save->dir.z,
		save->c1.i,save->c2.i, save->id);
		save = save->next;
	}
}

static void	debug_objs(t_obj *save, t_clip *clips)
{
	if (save != NULL)
		printf("\n\033[38;5;208mObjects : \n\n");
	while (save != NULL)
	{
		printf("\nType: %s\nTranslation: %f %f %f\nRotation: %f %f %f\n"
		"Variable: %f\nScale: %f\nColor: %06x argb(%d, %d, %d, %d)\nDiffuse: %f\nSpecular: %f\nReflexion: %f\nTexture: %p\nID: %d\n"
		"address: %p\nLinked to %p\n",
		g_ref[save->type].name, save->t.x, save->t.y, save->t.z,
		save->dir.x, save->dir.y, save->dir.z, save->v[0], save->scale,
		save->mat.color.i,
		save->mat.color.p.a, save->mat.color.p.r, save->mat.color.p.g,
		save->mat.color.p.b, save->mat.diff, save->mat.spec,save->mat.refl, save->mat.txt,
		save->id, save, save->grad);
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
		printf("Translation: %f %f %f\nPower: %f\nColor: %06x"
		"argb(%d, %d, %d, %d)\nID: %d\n\n",
		save->t.x, save->t.y, save->t.z,
		save->power, save->color.i, save->color.p.a, save->color.p.r, save->color.p.g,
		save->color.p.b, save->id);
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
		"ssaa: %d\nFOV: %d\nDimx : %d\nDimy : %d\nID: %d\n\n",
		save->t.x, save->t.y, save->t.z,
		save->dir.x, save->dir.y, save->dir.z,
		save->data.ssaa, (int)deg(save->data.fov), save->data.dimx,
		save->data.dimy, save->id);
		save = save->next;
	}
}

void		debug_prst(t_prst *p, int rec)
{
	while (p && (p->s.cams || p->s.lits || p->s.objs || p->s.grads))
	{
		printf("\n\n\n\033[38;5;96mPRESET (rec %d):\n", rec);
		printf("Translation: %f %f %f\nDirection: %f %f %f\nScale : %f\n",
		p->t.x, p->t.y, p->t.z, p->dir.x, p->dir.y, p->dir.z, p->scale);
		debug(p->s, rec++);
		p = p->next;
	}
}

void		debug_scene(t_scene	s)
{
	if (s.auto_l)
	{
		printf("\n\033[38;5;15mScene :\n\n");
		printf("Lights: Auto\n");
	}
}

void		debug(t_scene s, int rec)
{
	debug_scene(s);
	debug_cams(s.cams);
	debug_lits(s.lits);
	debug_grad(s.grads);
	debug_objs(s.objs, NULL);
	debug_prst(s.prsts, rec);
	if (s.cams && s.lits && s.grads && s.objs && s.prsts)
		printf("\033[38;5;203m%s\n", EMPTY_SCENE);
	printf("\033[0m");
}
