/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_deg_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:15:27 by kdouveno          #+#    #+#             */
/*   Updated: 2018/10/08 16:28:41 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		check_pt(t_deg *deg, char* l1, char *l2)
{
	if (!(ft_strcmp(l1, "tx")))
	{
		deg->t.x = ft_atod(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "ty")))
	{
		deg->t.y = ft_atod(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "tz")))
	{
		deg->t.z = ft_atod(l2);
		return (0);
	}
	return (1);
}

static int		check_arg(t_deg *deg, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "id")))
	{
		deg->id = l2;
		return (0);
	}
	if (!(ft_strcmp(l1, "color1")))
	{
		deg->color1 = (t_color)ft_atoi(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "color2")))
	{
		deg->color2 = (t_color)ft_atoi(l2);
		return (0);
	}
	return (1);
}

static int		check_rot(t_deg *deg, char* l1, char *l2)
{
	if (!(ft_strcmp(l1, "dirx")))
	{
		deg->dir.x = ft_atod(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "diry")))
	{
		deg->dir.y = ft_atod(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "dirz")))
	{
		deg->dir.z = ft_atod(l2);
		return (0);
	}
	return (1);
}

void			stock_deg(t_env *e, t_deg *deg, char *l1, char *l2)
{
	char	*cp;
	int		i;

	i = 0;
	cp = ft_str_tolower(l1);
	if (check_pt(deg, cp, l2) == 1 && check_arg(deg, cp, l2) == 1
	 && check_rot(deg, cp, l2) == 1)
	{
		while (is_ignored(l1[i]) == 1)
			i++;
		if (l1[i] != '\0')
			wrong_type(e, l1, 0, 0);
	}
	free(cp);
}

t_deg			*deg_parse_2(t_env *e, int fd)
{
	char	*line;
	int		res;
	char	*l1;
	char	*l2;
	t_deg	*deg;

	if (!(deg = malloc(sizeof(t_deg))))
		error(e, MALLOC_ERROR);
	*deg = (t_deg){(t_pt){0, 0, 0}, (t_vec){0, 0, 0}, NULL, 0 , 0, NULL};
	while ((res = get_next_line(fd, &line)) > 0
		&& get_prop(e, line, &l1, &l2) != 1)
	{
		stock_deg(e, deg, l1, l2);
		free(line);
		if (res == -1)
			error(e, READ_ERROR);
	}
	free(line);
	return (deg);
}

void			deg_parse(t_env *e, int type, int fd)
{
	t_deg	*save;

	(void)type;
	save = e->s.degs;
	if (save != NULL)
	{
		while(save->next != NULL)
			save = save->next;
		save->next = deg_parse_2(e, fd);
	}
	else
		e->s.degs = deg_parse_2(e, fd);
}
