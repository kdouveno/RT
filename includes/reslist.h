#ifndef RESLIST_H
# define RESLIST_H
# include "rt.h"

typedef struct			s_reslist
{
	double				t;
	t_obj				*o;
	struct s_reslist	*next;
}						t_reslist;

#endif
