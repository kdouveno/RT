/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:20:32 by gperez            #+#    #+#             */
/*   Updated: 2018/11/12 17:20:32 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parameter_thread_rec(t_env *e, char *argv, int i, int r)
{
	int		res;

	res = ft_atoi(&(argv[i]));
	res = res < 0 ? -res : res;
	if ((res != 0 && !r )|| (r && res < REC_FILE))
	{
		if (!r)
			e->glb.thread_count = res % 2 != 0 ? res + 1 : res;
		else
			e->glb.rec_lim_file = res;
		r ? printf("\033[38;5;40mRecursive limit changed to : %d\n\033[0m",
			e->glb.rec_lim_file)
			: printf("\033[38;5;40mThreads changed to : %d\n\033[0m",
			e->glb.thread_count);
	}
	else
		r ? ft_putstr("\033[38;5;203mRecursive number is not apply\n\033[0m")
			: ft_putstr("\033[38;5;203mThreads number is not apply\n\033[0m");
}

static void	parameter_shortcut(t_env *e, char *argv, int *d)
{
	if (ft_strcmp(argv, "d") == 0)
		*d = 1;
	else if (argv[0] == 't')
		parameter_thread_rec(e, argv, 1, 0);
	else if (argv[0] == 'r')
		parameter_thread_rec(e, argv, 1, 1);
	else
		error(e, USAGE);
}

static void	parameter_extended(t_env *e, char *argv, int *d)
{
	int i;

	i = 0;
	while (!(argv[i] >= '0' && argv[i] <= '9') && argv[i] != '\0')
		i++;
	if (!(ft_strcmp(argv, "debug")) && i == (int)ft_strlen("threads"))
		*d = 1;
	else if (!(ft_strncmp(argv, "threads", i))
		&& i == (int)ft_strlen("threads"))
		parameter_thread_rec(e, argv, i, 0);
	else if (!(ft_strncmp(argv, "recursive", i))
		&& i == (int)ft_strlen("recursive"))
		parameter_thread_rec(e, argv, i, 1);
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
	*e = (t_env){{NULL, 3, -1, THRD_CNT},
		{0,0}, {NULL, NULL, NULL, NULL, NULL,
			(t_color){(t_rgb){0,0,0,0}}}};
	while (i < argc)
	{
		if (argv[i][0] == '-')
			parameter(e, &(argv[i][1]), &d);
		else
			error(e, USAGE);
		i++;
	}
	if (check_file_ext(argv[1], ".rt"))
		error(e, EXT_ERROR);
	parse(e, argv[1], 0);
	if (d == 1)
		debug(e->s, 1);
}
