/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:22 by gperez            #+#    #+#             */
/*   Updated: 2018/10/28 20:02:51 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*get_name(t_env *e, char *line, int i, int *l)
{
	char	*cp;
	int		i_cp;

	while (line[i] != '{' && line[i] != '\0')
	{
		if (is_ignored(line[i]) == 0)
			(*l)++;
		i++;
	}
	if (*l == 0 && line[i] == '{')
	{
		*l = -1;
		return (NULL);
	}
	i = 0;
	i_cp = 0;
	if (!(cp = malloc(sizeof(char) * *l + 1)))
	{
		ft_memdel((void**)&line);
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

static int	link_name(char *name)
{
	int	i;
	int out;

	i = 0;
	while (*g_ref[i].name && ft_strcmp(g_ref[i].name, name))
		i++;
	if ((out = g_ref[i].name[0] != '\0' ? i : -1) >= 0)
		ft_memdel((void**)&name);
	return (out);
}

static void	parse_line(t_env *e, char *line, int fd)
{
	int			l;
	int			t;
	char		*type;
	char		*l_type;

	l = 0;
	type = get_name(e, line, 0, &l);
	if (type == NULL && l == -1)
	{
		ft_memdel((void**)&line);
		wrong_type(e, type, fd, 1);
		return ;
	}
	l_type = ft_str_tolower(type);
	ft_memdel((void**)&type);
	if (l_type[0] != '\0')
	{
		if ((t = link_name(l_type)) >= 0)
			g_ref[t].parse(e, t, fd);
		else
			wrong_type(e, l_type, fd, 1);
	}
	else
		ft_memdel((void**)&l_type);
	ft_memdel((void**)&line);
}

void		parse(t_env *e, char *arg, int prst)
{
	int		fd;
	int		check;
	char	*line;

	if ((fd = open(arg, O_RDONLY)) == -1)
		prst == 1 ? return (error(NULL, PRST_ERROR)) : error(e, OPEN_ERROR);
	while ((check = get_next_line(fd, &line)) > 0)
		parse_line(e, line, fd);
	ft_memdel((void**)&line);
	link_obj(e);
	if (check == -1)
		prst == 1 ? return (error(e->p, PRST_ERROR)) : error(e, READ_ERROR);
	if (close(fd) == -1)
		prst == 1 ? return (error(e->p, PRST_ERROR)) : error(e, CLOSE_ERROR);
}
