/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:22 by gperez            #+#    #+#             */
/*   Updated: 2018/10/04 12:07:03 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	a foutre dans un autre fichier utilitaire
*/

static int	is_name_char(char c)
{
	return (c == '_'
	|| (c >= 'a' && c <= 'z')
	|| (c >= 'A' && c <= 'Z')
	|| (c >= '0' && c <= '9')
	|| c == '.');
}

static int	is_ignored(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\r');
}

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
	if (cp = malloc(sizeof(char) * l + 1))
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
}

static int	link_name(const char *name)
{
	int	i;

	i = 0;
	while (strcomp(g_ref[i].prop, name))
		i++;
	if (g_ref[i].putin == NULL)
		return (-1);
	return (i);
}

static void skip_block(int fd, char *line)
{
	while ((check = get_next_line(fd, &line)) > 0)
	{
	}
	if (check == -1)
	{
		free(line);
		error(e, READ_ERROR);
	}
}

void	wrong_type(t_env *e, char *l_type, int fd)
{
	ft_putstr(l_type);
	ft_putendl(" is ignored.");
	free(l_type);
	skip_block(e, fd, line);
}

static void	parse_line(t_env *e, char *line, int fd)
{
	int			i;
	int			l;
	char		*type;
	char		*l_type;

	i = 0;
	l = 0;
	type = get_name(e, line, i, l);
	l_type = ft_str_to_lower(type);
	free(type);
	if (l_type[0] != '\0')
	{
		if ((t = link_name(l_type)) != TYPE_END)
			g_ref[(t = link_name(l_type))].putin(e, t, fd)
		else
			wrong_type(e, t_type, fd);
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
	t_scene	s;

	e->s = &s;
	s->objs = NULL;
	s->lits = NULL;
	s->cam = NULL;
	if ((fd = open(file, O_RDONLY)) == -1)
		error(e, OPEN_ERROR);
	while ((check = get_next_line(fd, &line)) > 0)
		parse_line(e, line, fd);
	if (check == -1)
		error(e, READ_ERROR);
	if (close(fd) == -1)
		error(e, CLOSE_ERROR);
}

void	get_prop(char *line, char *pair[2])
{
	int i;
	int	quad[5];

	i = 0;
	quad = (int[5]){-1, 0, -1, 0, 0};
	while (line[i])
	{
		if (is_name_char(line[i]))
		{
			if (quad[0 + quad[4]] == -1)
				quad[0 + quad[4]] = i;
			quad[1 + quad[4]]++;
		}
		else if (line[i] == ':')
			quad[4] = 2;
	}
	if (!(pair[0] = (char*)malloc(sizeof(char) * quad[1]))
	|| !(pair[1] = (char*)malloc(sizeof(char) * quad[3])))
		error(e, MALLOC_ERROR);

}

void	parse_cams(t_env *e, t_objtype type, int fd)
{
	char	*line;
	int		ret;
	char	*pair[2];
	while ((res = get_next_line(fd, &line)) > 0)
	{
		tab = q
		free(line);
	}
}
