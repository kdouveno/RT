/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_mat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:18:00 by gperez            #+#    #+#             */
/*   Updated: 2018/11/12 17:18:00 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rt.h"

void	stock_mat(t_env *e, t_obj *obj, char *l1, char *l2)
{
	char	*cp;
	int		i;

	i = 0;
	cp = ft_str_tolower(l1);
	if (check_mat(e, obj, cp, l2) == 1)
	{
		while (is_ignored(l1[i]) == 1)
			i++;
		if (l1[i] != '\0')
			wrong_type(e, l1, 0, 0);
	}
	ft_memdel((void**)&cp);
}

void	link_obj_mat(t_env *e, t_obj *obj, int fd)
{
	char	*line;
	int		res;
	char	*l1;
	char	*l2;

	while ((res = get_next_line(fd, &line)) > 0
		&& get_prop(e, line, &l1, &l2) != 1)
	{
		stock_mat(e, obj, l1, l2);
		ft_memdel((void**)&l1);
		ft_memdel((void**)&l2);
		ft_memdel((void**)&line);
		if (res == -1)
			error(e, READ_ERROR);
	}
	ft_memdel((void**)&line);
}

static void	parse_line(t_env *e, t_obj *obj, char *line, t_fd fd)
{
	int			l;
	char		*type;
	char		*l_type;
	char		*name;

	l = 0;
	type = get_name(e, line, 0, &l);
	if (type == NULL && l == -1)
	{
		ft_memdel((void**)&line);
		wrong_type(e, type, fd.fd, 1);
		return ;
	}
	l_type = ft_str_tolower(type);
	ft_memdel((void**)&type);
	name = file_name(fd.file);
	if (!(strcmp(l_type, name)))
	{
		link_obj_mat(e, obj, fd.fd);
	}
	ft_memdel((void**)&name);
	ft_memdel((void**)&l_type);
	ft_memdel((void**)&line);
}

void	link_mat(t_env *e, t_obj *obj, char *file)
{
	t_fd		fd;
	int			check;
	char		*line;

	fd.file = file;
	if ((fd.fd = open(file, O_RDONLY)) == -1)
	{
		ft_putstr("\033[38;5;203mFail to open the file ");
		ft_putstr(file);
		ft_putstr("\033[0m");
		ft_putchar('\n');
		return;
	}
	while ((check = get_next_line(fd.fd, &line)) > 0)
		parse_line(e, obj, line, fd);
	ft_memdel((void**)&line);
	if (check == -1)
		error(e, READ_ERROR);
	if (close(fd.fd) == -1)
		error(e, CLOSE_ERROR);
	ft_memdel((void**)&file);
}
