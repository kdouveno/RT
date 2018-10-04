/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:22 by gperez            #+#    #+#             */
/*   Updated: 2018/10/04 15:34:37 by gperez           ###   ########.fr       */
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
	return (*g_ref[i].name ? i : -1);
}

static void skip_block(t_env *e, int fd)
{
	int		check;
	char	*line;

	while ((check = get_next_line(fd, &line)) > 0 && line[0] != '}')
	{
	}
	if (check == -1)
	{
		free(line);
		error(e, READ_ERROR);
	}
	free(line);
}

void	wrong_type(t_env *e, char *l_type, int fd)
{
	ft_putstr(l_type);
	ft_putendl(" is ignored.");
	free(l_type);
	skip_block(e, fd);
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
			wrong_type(e, l_type, fd);
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

void	get_prop2(char *line, char *l1, char *l2, int trio[3])
{
	int i;
	int j;

	i = 0;
	j = 0;
	trio[2] = 0;
	while (line[i])
	{
		if (is_name_char(line[i]))
		{
			if (trio[2])
				l1[j] = line[i];
			else
				l2[j] = line[i];
			j++;
		}
		else if (line[i] == ':')
		{
			trio[2] = 1;
			j = 0;
		}
		i++;
	}
	l1[trio[0]] = '\0';
	l2[trio[1]] = '\0';
}

void	get_prop(t_env *e, char *line, char **l1, char **l2)
{
	int i;
	int	trio[3];

	i = 0;
	trio[0] = 0;
	trio[1] = 0;
	trio[2] = 0;
	while (line[i])
	{
		if (is_name_char(line[i]))
			trio[1 + trio[2]]++;
		else if (line[i] == ':')
			trio[2] = 2;
		i++;
	}
	if (!(*l1 = (char*)malloc(sizeof(char) * (trio[0] + 1)))
	|| !(*l2 = (char*)malloc(sizeof(char) * (trio[1] + 1))))
		error(e, MALLOC_ERROR);

	get_prop2(line, *l1, *l2, trio);
}

void	cam_parse(t_env *e, int type, int fd)
{
	char	*line;
	int		res;
	char	*l1;
	char	*l2;

	(void)type;
	while ((res = get_next_line(fd, &line)) > 0)
	{

		get_prop(e, line, &l1, &l2);
		printf("j'aborte apres la\n");

		ft_putendl(l1);
		ft_putendl(l2);
		free(line);
	}
}
