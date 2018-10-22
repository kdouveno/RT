#include "rt.h"

static void	parameter_shortcut(t_env *e, char *argv, int *d)
{
	if (ft_strcmp(argv, "d") == 0)
		*d = 1;
	else
		error(e, USAGE);
}

static void	parameter_extended(t_env *e, char *argv, int *d)
{
	if (ft_strcmp(argv, "debug") == 0)
		*d = 1;
	else
		error(e, USAGE);
}

static void	parameter(t_env *e, char *argv, int *d)
{
	if (argv[0] == '-')
		parameter_extended(e, &(argv[1]), d);
	else
		parameter_shortcut(e, argv, d);
}

void	arg(t_env *e, int argc, char **argv)
{
	int	i;
	int	d;

	i = 2;
	d = 0;
	e->s.objs = NULL;
	e->s.lits = NULL;
	e->s.cams = NULL;
	e->s.grads = NULL;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			parameter(e, &(argv[i][1]), &d);
		else
			error(e, USAGE);
		i++;
	}
	parse(e, argv[1]);
	if (d == 1)
		debug(e);
}
