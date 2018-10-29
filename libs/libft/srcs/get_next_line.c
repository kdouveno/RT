/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 11:16:46 by kdouveno          #+#    #+#             */
/*   Updated: 2018/10/29 13:32:51 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"
#include <stdio.h>

t_gnl	*fetch(t_gnl **data, const int fd)
{
	t_gnl	*d;
	t_gnl	*out;

	d = *data;
	while (d && d->next)
	{
		if (d->fd == fd)
			break ;
		d = d->next;
	}
	if (!d || d->fd != fd)
	{
		out = (t_gnl*)malloc(sizeof(t_gnl));
		*out = (t_gnl){"", 0, fd, NULL};
		if (!d)
			*data = out;
		else
			d->next = out;
		d = !d ? *data : d->next;
	}
	return (d);
}

int		addata(t_gnl *data, char **line)
{
	char *next;
	char *tmp;
	char *fre;

	tmp = data->c + data->pos;
	next = ft_strchr(tmp, '\n');
	if (next)
	{
		*next = '\0';
		fre = *line;
		if (!(*line = ft_strjoin(*line ? *line : "", tmp)))
			return (-1);
		free(fre);
		data->pos += next - tmp + 1;
		return (1);
	}
	fre = *line;
	if (!(*line = ft_strjoin(*line ? *line : "", tmp)))
		return (-1);
	*(data->c) = '\0';
	data->pos = 0;
	free(fre);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl	*data;
	t_gnl			*cur;
	int				out;
	int				ret;

	if (!line)
		return (-1);
	*line = NULL;
	cur = fetch(&data, fd);
	ret = 1;
	while (!(out = addata(cur, line)))
	{
		if ((ret = read(fd, cur->c, BUFF_SIZE)) > 0)
		{
			cur->c[ret] = '\0';
			cur->pos = 0;
			continue ;
		}
		break ;
	}
	if (out == -1 || ret == -1)
		return (-1);
	!**line && !ret ? free() : 0;
	return (!**line && !ret ? 0 : 1);
}
