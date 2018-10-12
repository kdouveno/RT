/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_wrong_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:46:05 by gperez            #+#    #+#             */
/*   Updated: 2018/10/12 14:06:02 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void skip_block(t_env *e, int fd)
{
	int		check;
	char	*line;

	while ((check = get_next_line(fd, &line)) > 0 && line[0] != '}')
		;
	if (check == -1)
	{
		free(line);
		error(e, READ_ERROR);
	}
	free(line);
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
		free(l_type);
	}
	ft_putstr("\033[0m");
	if (skip)
		skip_block(e, fd);
}
