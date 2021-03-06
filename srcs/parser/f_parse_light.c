/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:41:13 by gperez            #+#    #+#             */
/*   Updated: 2019/01/15 15:41:46 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_arg2(t_lit *lit, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "radius")))
		lit->radius = get_coef(ft_atod(l2));
	else
		return (1);
	return (0);
}

int		check_arg(t_lit *lit, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "id")))
	{
		lit->id = ft_atoi(l2);
		lit->id = lit->id < 0 ? -lit->id : lit->id;
	}
	else if (!(ft_strcmp(l1, "power")))
		lit->power = ft_atod(l2);
	else if (!(ft_strcmp(l1, "c")) || !(ft_strcmp(l1, "color")))
	{
		if (l2[0] == '#')
			lit->color.i = (unsigned)atoi_hexa(&l2[1]);
		else
			lit->color.i = ft_atoi(l2);
	}
	else
		return (1);
	return (0);
}

void	stock_light(t_env *e, t_lit *lit, char *l1, char *l2)
{
	char	*cp;
	int		i;

	i = 0;
	cp = ft_str_tolower(l1);
	if (check_loc(e, lit, cp, l2) && check_pt(lit, cp, l2) == 1
		&& check_arg(lit, cp, l2) == 1
		&& check_arg2(lit, cp, l2) == 1)
	{
		while (is_ignored(l1[i]) == 1)
			i++;
		if (l1[i] != '\0')
			wrong_type(e, l1, 0, 0);
	}
	ft_memdel((void**)&cp);
}

t_lit	*parse_light_2(t_env *e, int fd)
{
	char	*line;
	int		res;
	char	*l1;
	char	*l2;
	t_lit	*lit;

	if (!(lit = ft_memalloc(sizeof(t_lit))))
		error(e, MALLOC_ERROR);
	*lit = (t_lit){NULL, zero_matrix(), -1, 1.0f, 0.0f, {0, 0, 0},
		(t_color){(t_rgb){255, 255, 255, 255}}, {0, 0, 0, 0}};
	while ((res = get_next_line(fd, &line)) > 0
		&& get_prop(e, line, &l1, &l2) != 1)
	{
		stock_light(e, lit, l1, l2);
		ft_memdel((void**)&l1);
		ft_memdel((void**)&l2);
		ft_memdel((void**)&line);
		if (res == -1)
			error(e, READ_ERROR);
	}
	ft_memdel((void**)&line);
	return (lit);
}

void	parse_light(t_env *e, int type, int fd, t_scene *s)
{
	t_lit	*save;

	(void)type;
	save = s->lits;
	if (save != NULL)
	{
		while (save->next != NULL)
			save = save->next;
		save->next = parse_light_2(e, fd);
	}
	else
		s->lits = parse_light_2(e, fd);
}
