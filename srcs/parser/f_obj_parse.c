/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_obj_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:28:19 by kdouveno          #+#    #+#             */
/*   Updated: 2018/10/15 15:57:03 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		check_arg(t_obj *obj, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "v")))
	{
		obj->v1 = ft_atod(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "color")))
	{
		obj->color = (t_color)ft_atoi(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "id")))
	{
		obj->id = ft_atoi(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "disp")))
	{
		obj->disp = l2[0];
		return (0);
	}
	return(1);
}

static int		check_mat(t_obj *obj, char* l1, char *l2)
 {
	 if (!(ft_strcmp(l1, "diff")))
 	{
 		obj->diff = ft_atod(l2);
 		return (0);
 	}
	if (!(ft_strcmp(l1, "spec")))
	{
		obj->spec = ft_atod(l2);
		return (0);
	}
	return (1);
 }

void	stock_obj(t_env *e, t_obj *obj, char *l1, char *l2)
{
	char	*cp;
	int		i;

	i = 0;
	cp = ft_str_tolower(l1);
	if (check_pt(obj, cp, l2) == 1 && check_arg(obj, cp, l2 ) == 1 &&
		check_rot(obj, cp, l2) == 1 && check_mat(obj, cp, l2) == 1)
	{
		while (is_ignored(l1[i]) == 1)
			i++;
		if (l1[i] != '\0')
			wrong_type(e, l1, 0, 0);
		free(cp);
	}
}

t_obj	*obj_parse_2(t_env *e, int type, int fd)
{
	char	*line;
	int		res;
	char	*l1;
	char	*l2;
	t_obj	*obj;

	if (!(obj = malloc(sizeof(t_obj))))
		error(e, MALLOC_ERROR);
	*obj = (t_obj){(t_pt){0, 0, 0}, (t_rot){0, 0, 0}, type,
		0, (t_color)0, 0, 0, 0, '\0', NULL, NULL, NULL};
	while ((res = get_next_line(fd, &line)) > 0 && get_prop(e, line, &l1, &l2) != 1)
	{
		stock_obj(e, obj, l1, l2);
		free(line);
		if (res == -1)
			error(e, READ_ERROR);
	}
	free(l1);
	free(l2);
	free(line);
	return (obj);
}

void	obj_parse(t_env *e, int type, int fd)
{
	t_obj	*save;

	save = e->s.objs;
	if (save != NULL)
	{
		while(save->next != NULL)
			save = save->next;
		save->next = obj_parse_2(e, type, fd);
	}
	else
		e->s.objs = obj_parse_2(e, type, fd);
}
