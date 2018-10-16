
#include "rt.h"

void		creat_clips(t_env *e, t_obj *obj, char *l2)
{
	t_clip	*new;
	t_clip	*cp;

	cp = obj->clips;
	if (!(new = malloc(sizeof(t_clip))))
		error(e, MALLOC_ERROR);
	*new = (t_clip){atoi(l2), NULL, NULL};
	if (cp != NULL)
	{
		while (cp->next != NULL)
			cp = cp->next;
		cp->next = new;
	}
	else
		obj->clips = new;
}
