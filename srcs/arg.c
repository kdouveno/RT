#include "rt.h"

static void	parameter_shortcut(t_env *e, char *argv, int *d)
{
	int		res;

	if (ft_strcmp(argv, "d") == 0)
		*d = 1;
	else if (argv[0] == 't')
	{
		if (argv[1] <= '0' || argv[1] > '9')
		{
			ft_putstr("\033[38;5;203mThreads number is not apply\n\033[0m");
			return;
		}
		res = ft_atoi(&(argv[1]));
		res = res < 0 ? -res : res;
		e->glb.thread_count = res % 2 != 0 ? res + 1 : res;
		printf("\033[38;5;40mThreads is changed to : %d\n\033[0m",
			e->glb.thread_count);
	}
	else
		error(e, USAGE);
}

static void	parameter_extended(t_env *e, char *argv, int *d)
{
	int i;
	int res;

	i = 0;
	while (!(argv[i] >= '0' && argv[i] <= '9') && argv[i] != '\0')
		i++;
	if (ft_strcmp(argv, "debug") == 0)
		*d = 1;
	else if (ft_strncmp(argv, "threads", i) == 0 && i == (int)ft_strlen("threads"))
	{
		res = ft_atoi(&(argv[i]));
		res = res < 0 ? -res : res;
		if (res != 0)
		{
			e->glb.thread_count = res % 2 != 0 ? res + 1 : res;
			printf("\033[38;5;40mThreads is changed to : %d\n\033[0m",
				e->glb.thread_count);
		}
		else
			ft_putstr("\033[38;5;203mThreads number is not apply\n\033[0m");
	}
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
	*e = (t_env){{NULL, 100}, {0,0}, {NULL, NULL, NULL, NULL}, NULL};
	while (i < argc)
	{
		if (argv[i][0] == '-')
			parameter(e, &(argv[i][1]), &d);
		else
			error(e, USAGE);
		i++;
	}
	parse(e, argv[1], 0);
	if (d == 1)
		debug(e);
}
