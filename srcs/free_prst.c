#include "rt.h"

void	free_prst(t_prst *p)
{
	if (p)
	{
		if (p->next)
			free_prst(p->next);
		free_scene(&(p->s));
		ft_memdel((void**)&p);
	}
}
