/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:41:23 by gperez            #+#    #+#             */
/*   Updated: 2019/01/11 15:06:41 by gperez           ###   ########.fr       */
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
		"Color2: %06x\nID: %d\nOrigin: %d %p (%f, %f, %f)\n\n",
		save->m.t.x, save->m.t.y, save->m.t.z,
		save->r.x, save->r.y, save->r.z,
		save->c1.i, save->c2.i, save->id, save->m.l.id, save->m.l.target,
			save->m.pt.x, save->m.pt.y, save->m.pt.z);
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
		"Variable: %f\nScale: %f\nColor: %06x argb(%d, %d, %d, %d)\n"
		"Diffuse: %f\nSpecular: %f\nReflexion: %f\nTexture: %p\nID: %d\n"
		"address: %p\nLinked to %p\nOrigin: %d %p (%f, %f, %f)\n",
		g_ref[save->type].name, save->m.t.x, save->m.t.y, save->m.t.z,
		save->m.rot.x, save->m.rot.y, save->m.rot.z, save->v[0], save->m.scale,
		save->mat.color.i, save->mat.color.p.a, save->mat.color.p.r,
		save->mat.color.p.g, save->mat.color.p.b, save->mat.diff,
		save->mat.spec, save->mat.refl, save->mat.txt, save->id, save,
		save->grad, save->m.l.id, save->m.l.target, save->m.pt.x, save->m.pt.y,
		save->m.pt.z);
		printf("\033[38;5;136m");
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
		"argb(%d, %d, %d, %d)\nID: %d\nOrigin: %d %p (%f, %f, %f)\n\n",
		save->m.t.x, save->m.t.y, save->m.t.z, save->power, save->color.i,
		save->color.p.a, save->color.p.r, save->color.p.g, save->color.p.b,
		save->id, save->m.l.id, save->m.l.target, save->m.pt.x, save->m.pt.y,
		save->m.pt.z);
		printf("%p\n", &save->m);
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
		"ssaa: %d\nFOV: %f\nDimx : %d\nDimy : %d\nID: %d\n"
		"Origin: %d %p (%f, %f, %f)\n\n",
		save->m.t.x, save->m.t.y, save->m.t.z, save->m.rot.x, save->m.rot.y,
		save->m.rot.z, save->data.ssaa, save->data.fov, save->data.dimx,
		save->data.dimy, save->id, save->m.l.id, save->m.l.target, save->m.pt.x,
		save->m.pt.y, save->m.pt.z);
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

void		debug_scene(t_scene s)
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
