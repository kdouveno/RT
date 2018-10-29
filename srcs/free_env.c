#include "rt.h"

static void	free_clip(t_clip *clip)
{
	t_clip	*next;

	while (clip != NULL)
	{
		next = clip->next;
		ft_memdel((void**)&clip);
	//	printf("\033[38;5;164mClip clean\n");
		clip = next;
	}
}

static void	free_obj(t_obj *obj)
{
	t_obj 	*next;

	while (obj != NULL)
	{
		next = obj->next;
		free_clip(obj->clips);
		ft_memdel((void**)&obj);
	//	printf("\033[38;5;164mObj clean\n");
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
	//	printf("\033[38;5;164mLit clean\n");
		lit = next;
	}
}

static void	free_cam(t_cam *cam)
{
	t_cam	*next;

	while (cam != NULL)
	{
		next = cam->next;
		ft_memdel((void**)&cam);
	//	printf("\033[38;5;164mCam clean\n");
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
	//	printf("\033[38;5;164mGrad clean\n");
		grad = next;
	}
}

void		free_scene(t_scene *s)
{
	free_obj(s->objs);
	free_lit(s->lits);
	free_cam(s->cams);
	free_grad(s->grads);
//	printf("\033[0m\n");
}
