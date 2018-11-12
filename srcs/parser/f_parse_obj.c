/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:28:19 by kdouveno          #+#    #+#             */
/*   Updated: 2018/11/12 15:31:52 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		check_arg(t_env *e, t_obj *obj, char *l1, char *l2)
{
	int out;

	out = 1;
	if (!(ft_strcmp(l1, "v1")) && !(out = 0))
		obj->v[0] = ft_atod(l2);
	else if (!(ft_strcmp(l1, "v2")) && !(out = 0))
		obj->v[1] = ft_atod(l2);
	else if (!(ft_strcmp(l1, "v3")) && !(out = 0))
		obj->v[2] = ft_atod(l2);
	else if (!(ft_strcmp(l1, "id")) && !(out = 0))
	{
		obj->id = ft_atoi(l2);
		obj->id = obj->id < 0 ? -obj->id : obj->id;
	}
	else if (!(ft_strcmp(l1, "clip")) && !(out = 0))
		creat_clips(e, obj, l2);
	return (out);
}

int		check_mat(t_env *e, t_obj *obj, char* l1, char *l2)
 {
	if (!(ft_strcmp(l1, "mat")))
 	{
 		if (check_file_ext(l2, ".mat") && l2[0])
 			wrong_type(e, l1, 0, 0);
 		else if (l2[0])
 			link_mat(e, obj, ft_strjoin("mat/", l2));
 		return (0);
 	}
	else if (!(ft_strcmp(l1, "diff")))
 	{
 		obj->mat.diff = ft_atod(l2);
 		return (0);
 	}
	else if (!(ft_strcmp(l1, "spec")))
	{
		obj->mat.spec = ft_atod(l2);
		return (0);
	}
	else if (!(ft_strcmp(l1, "color")))
	{
		parse_color(obj, l2, NULL, 0);
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
	if (check_pt(obj, cp, l2) == 1 && check_arg(e, obj, cp, l2 ) == 1
			&& check_rot(obj, cp, l2) == 1 && check_mat(e, obj, cp, l2) == 1
					&& check_dir(obj, cp, l2) == 1)
	{
		while (is_ignored(l1[i]) == 1)
			i++;
		if (l1[i] != '\0')
			wrong_type(e, l1, 0, 0);
	}
	ft_memdel((void**)&cp);
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
	*obj = (t_obj){(t_pt){0, 0, 0}, (t_vec){0, 0, 0}, -1, type, {},
		(t_mat){(t_color){(t_rgb){255,255,255,255}}, 0, 0}, {0, 0, 0, 0}, -1,
		NULL, NULL, NULL, NULL};
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

void	obj_parse(t_env *e, int type, int fd, t_scene *s)
{
	t_obj	*save;

	save = s->objs;
	if (save != NULL)
	{
		while(save->next != NULL)
			save = save->next;
		save->next = obj_parse_2(e, type, fd);
	}
	else
		s->objs = obj_parse_2(e, type, fd);
}
