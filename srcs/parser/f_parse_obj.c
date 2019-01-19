/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:28:19 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/19 14:14:40 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		check_arg(t_env *e, t_obj *obj, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "id")))
	{
		obj->id = ft_atoi(l2);
		obj->id = obj->id < 0 ? -obj->id : obj->id;
	}
	else if (!(ft_strcmp(l1, "clip")))
		creat_clips(e, obj, l2);
	else if (!(ft_strcmp(l1, "scale")))
		obj->m.scale = ft_atod(l2);
	else
		return (1);
	return (0);
}

void			stock_obj(t_env *e, t_obj *obj, char *l1, char *l2)
{
	char	*cp;
	int		i;

	i = 0;
	cp = ft_str_tolower(l1);
	if (check_loc(e, obj, cp, l2) && check_pt(obj, cp, l2)
		&& check_arg(e, obj, cp, l2) && check_rot(obj, cp, l2)
		&& check_mat(e, obj, cp, l2) && check_dir(obj, cp, l2)
		&& check_value(obj, cp, l2))
	{
		while (is_ignored(l1[i]) == 1)
			i++;
		if (l1[i] != '\0')
			wrong_type(e, l1, 0, 0);
	}
	ft_memdel((void**)&cp);
}

t_obj			*parse_obj_2(t_env *e, int type, int fd)
{
	char	*line;
	int		res;
	char	*l1;
	char	*l2;
	t_obj	*obj;

	if (!(obj = malloc(sizeof(t_obj))))
		error(e, MALLOC_ERROR);
	*obj = (t_obj){NULL, zero_matrix(), -1, type, {0, 0, 0, 0},
		(t_mat){(t_color){(t_rgb){255, 255, 255, 255}}, 1, 0, 0, 0, 1, 0, 0,
		BMP_LEVEL, NULL, NULL}, {0, 0, 0, 0}, NULL, NULL, NULL};
	while ((res = get_next_line(fd, &line)) > 0
		&& get_prop(e, line, &l1, &l2) != 1)
	{
		stock_obj(e, obj, l1, l2);
		ft_memdel((void**)&l1);
		ft_memdel((void**)&l2);
		ft_memdel((void**)&line);
		if (res == -1)
			error(e, READ_ERROR);
	}
	ft_memdel((void**)&line);
	return (obj);
}

void			parse_obj(t_env *e, int type, int fd, t_scene *s)
{
	t_obj	*save;

	save = s->objs;
	if (save != NULL)
	{
		while (save->next != NULL)
			save = save->next;
		save->next = parse_obj_2(e, type, fd);
	}
	else
		s->objs = parse_obj_2(e, type, fd);
}
