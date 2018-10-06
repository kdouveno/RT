/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:22 by gperez            #+#    #+#             */
/*   Updated: 2018/10/04 16:50:10 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	a foutre dans un autre fichier utilitaire
*/

static char	*get_name(t_env *e, char *line, int i, int l)
{
	char	*cp;
	int		i_cp;

	while (line[i] != '{' && line[i] != '\0')
	{
		if (is_ignored(line[i]) == 0)
			l++;
		i++;
	}
	i = 0;
	i_cp = 0;
	if (!(cp = malloc(sizeof(char) * l + 1)))
	{
		free(line);
		error(e, MALLOC_ERROR);
	}
	while (line[i] != '{' && line[i] != '\0')
	{
		if (is_ignored(line[i]) == 0)
		{
			cp[i_cp] = line[i];
			i_cp++;
		}
		i++;
	}
	cp[i_cp] = '\0';
	return (cp);
}

static int	link_name(const char *name)
{
	int	i;

	i = 0;
	while (ft_strcmp(g_ref[i].name, name) && *g_ref[i].name)
		i++;
	return (g_ref[i].name[0] != '\0' ? i : -1);
}

static void	parse_line(t_env *e, char *line, int fd)
{
	int			i;
	int			l;
	int			t;
	char		*type;
	char		*l_type;

	(void)fd;
	i = 0;
	l = 0;
	type = get_name(e, line, i, l);
	l_type = ft_str_tolower(type);
	free(type);
	if (l_type[0] != '\0')
	{
		if ((t = link_name(l_type)) >= 0)
		{
			ft_putendl(g_ref[t].name);
			g_ref[t].parse(e, t, fd);
		}
		else
			wrong_type(e, l_type, fd, 1);
	}
	else
		free(l_type);
	free(line);
}

void		parse(t_env *e, char *arg)
{
	int		fd;
	int		check;
	char	*line;

	e->s.objs = NULL;
	e->s.lits = NULL;
	e->s.cam = NULL;
	if ((fd = open(arg, O_RDONLY)) == -1)
		error(e, OPEN_ERROR);
	while ((check = get_next_line(fd, &line)) > 0)
		parse_line(e, line, fd);
	if (check == -1)
		error(e, READ_ERROR);
	if (close(fd) == -1)
		error(e, CLOSE_ERROR);
}
