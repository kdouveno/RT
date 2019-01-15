/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:20:41 by gperez            #+#    #+#             */
/*   Updated: 2019/01/15 16:01:08 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	free_clip(t_clip *clip)
{
	t_clip	*next;

	while (clip != NULL)
	{
		next = clip->next;
		ft_memdel((void**)&clip);
		clip = next;
	}
}

static void	free_clipin(t_objlist *clipin)
{
	t_objlist	*next;

	while (clipin != NULL)
	{
		next = clipin->next;
		ft_memdel((void**)&clipin);
		clipin = next;
	}
}

static void	free_obj(t_obj *obj)
{
	t_obj	*next;

	while (obj != NULL)
	{
		next = obj->next;
		free_clip(obj->clips);
		free_clipin(obj->clipping);
		(obj->mat.txt) ? SDL_FreeSurface(obj->mat.txt) : 0;
		(obj->mat.txt_bm) ? SDL_FreeSurface(obj->mat.txt_bm) : 0;
		ft_memdel((void**)&obj);
		obj = next;
	}
}

static void	free_lit(t_lit *lit)
{
	t_lit	*next;

	while (lit != NULL)
	{
		next = lit->next;
		ft_memdel((void**)&lit);
		lit = next;
	}
}

static void	free_cam(t_cam *cam)
{
	t_cam	*next;

	while (cam != NULL)
	{
		next = cam->next;
		(cam->data.render) ? SDL_FreeSurface(cam->data.render) : 0;
		ft_memdel((void**)&cam);
		cam = next;
	}
}

static void	free_grad(t_grad *grad)
{
	t_grad	*next;

	while (grad != NULL)
	{
		next = grad->next;
		ft_memdel((void**)&grad);
		grad = next;
	}
}

void		free_scene(t_scene *s)
{
	free_obj(s->objs);
	free_lit(s->lits);
	free_cam(s->cams);
	free_grad(s->grads);
	free_prst(s->prsts);
}
