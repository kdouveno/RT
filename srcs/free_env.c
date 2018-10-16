#include "rt.h"

static void	free_clip(t_clip *clip)
{
	t_clip	*next;

	while (clip != NULL)
	{
		next = clip->next;
		free(clip);
		printf("\033[38;5;164mClip clean\n");
		clip = next;
	}
}

static void	free_obj(t_obj *obj)
{
	t_obj 	*next;
	//t_clip	*next_clip;

	while (obj != NULL)
	{
		next = obj->next;
		/*while (obj->clips != NULL)
		{
			next_clip = obj->clips->next;
			free(obj->clips);
			printf("\033[38;5;164mClip clean\n");
			obj->clips = next_clip;
		}*/
		free_clip(obj->clips);
		free(obj);
		printf("\033[38;5;164mObj clean\n");
		obj = next;
	}


}

static void	free_lit(t_lit *lit)
{
	t_lit	*next;

	while (lit != NULL)
	{
		next = lit->next;
		free(lit);
		printf("\033[38;5;164mLit clean\n");
		lit = next;
	}
}

static void	free_cam(t_cam *cam)
{
	t_cam	*next;

	while (cam != NULL)
	{
		next = cam->next;
		free(cam);
		printf("\033[38;5;164mCam clean\n");
		cam = next;
	}
}

static void	free_grad(t_grad *grad)
{
	t_grad	*next;

	while (grad != NULL)
	{
		next = grad->next;
		free(grad);
		printf("\033[38;5;164mGrad clean\n");
		grad = next;
	}
}

void		free_env(t_env *e)
{
	free_obj(e->s.objs);
	free_lit(e->s.lits);
	free_cam(e->s.cams);
	free_grad(e->s.grads);
}