/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:22 by gperez            #+#    #+#             */
/*   Updated: 2018/10/03 16:00:31 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	a foutre dans un autre fichier utilitaire
*/

static int	is_name_char(char c)
{
	return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

static int	is_ignored(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\r');
}

static void	parse_line(t_env *e, char *line)
{
	int	i;

	while (line[i] != '{' && line[i] != '\0')
	{
		i++;
	}
	free(line);
}

void		parse(t_env *e, char *arg)
{
	int		fd;
	int		check;
	char	*line;
	t_scene	s;

	e->s = &s;
	s->objs = NULL;
	s->lits = NULL;
	s->cam = NULL;
	if ((fd = open(file, O_RDONLY)) == -1)
		error(e, OPEN_ERROR);
	while ((check = get_next_line(fd, &line)) > 0)
		parse_line(e, line);
	if (check == -1)
		error(e, READ_ERROR);
	if (close(fd) == -1)
		error(e, CLOSE_ERROR);
}
