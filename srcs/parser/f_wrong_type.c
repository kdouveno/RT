/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_wrong_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:46:05 by gperez            #+#    #+#             */
/*   Updated: 2018/11/12 17:18:17 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void skip_block(t_env *e, int fd)
{
	int		check;
	char	*line;

	while ((check = get_next_line(fd, &line)) > 0 && line[0] != '}')
		ft_memdel((void**)&line);
	if (check == -1)
	{
		ft_memdel((void**)&line);
		error(e, READ_ERROR);
	}
	ft_memdel((void**)&line);
}

void	wrong_type(t_env *e, char *l_type, int fd, int skip)
{
	ft_putstr("\033[2;49;91m");
	if (l_type == NULL)
		ft_putendl("A block is empty.");
	else
	{
		ft_putstr(l_type);
		ft_putendl(" is ignored.");
	}
	ft_putstr("\033[0m");
	if (skip)
	{
		ft_memdel((void**)&l_type);
		skip_block(e, fd);
	}
}
