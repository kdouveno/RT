/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cam_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:49:52 by gperez            #+#    #+#             */
/*   Updated: 2018/10/15 12:49:26 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_pt(void *cam, char* l1, char *l2)
{
	t_obj *obj;

	obj = (t_obj*)cam;
	if (!(ft_strcmp(l1, "tx")))
	{
		obj->t.x = ft_atod(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "ty")))
	{
		obj->t.y = ft_atod(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "tz")))
	{
		obj->t.z = ft_atod(l2);
		return (0);
	}
	return (1);
}

static int		check_arg(t_cam *cam, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "antialiasing")))
	{
		cam->antialia = atoi(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "id")))
	{
		cam->id = ft_strdup(l2);
		return (0);
	}
	return(1);
}

int		check_rot(void *cam, char* l1, char *l2)
{
	t_obj *obj;

	obj = (t_obj*)cam;
	if (!((ft_strcmp(l1, "dirx") && (ft_strcmp(l1, "rx")))))
	{
		obj->r.x = ft_atod(l2);
		return (0);
	}
	if (!((ft_strcmp(l1, "diry") && (ft_strcmp(l1, "ry")))))
	{
		obj->r.y = ft_atod(l2);
		return (0);
	}
	if (!((ft_strcmp(l1, "dirz") && (ft_strcmp(l1, "rz")))))
	{
		obj->r.z = ft_atod(l2);
		return (0);
	}
	return (1);
}

void	stock_cam(t_env *e, t_cam *cam, char *l1, char *l2)
{
	char	*cp;
	int		i;

	i = 0;
	cp = ft_str_tolower(l1);
	if (check_pt(cam, cp, l2) == 1 && check_rot(cam, cp, l2) == 1
		&& check_arg(cam, cp, l2 ) == 1)
	{
		while (is_ignored(l1[i]) == 1)
			i++;
		if (l1[i] != '\0')
			wrong_type(e, l1, 0, 0);
	}
	free(cp);
}

t_cam	*cam_parse_2(t_env *e, int fd)
{
	char	*line;
	int		res;
	char	*l1;
	char	*l2;
	t_cam	*cam;

	if (!(cam = malloc(sizeof(t_cam))))
		error(e, MALLOC_ERROR);
	*cam = (t_cam){(t_pt){0, 0, 0}, (t_vec){0, 0, 0}, (t_vec){0, 0, 0},
	(t_vec){0, 0, 0}, (t_pt){0,0,0}, 0, NULL, NULL};
	while ((res = get_next_line(fd, &line)) > 0 &&
		get_prop(e, line, &l1, &l2) != 1)
	{
		stock_cam(e, cam, l1, l2);
		free(line);
		if (res == -1)
			error(e, READ_ERROR);
	}
	free(l1);
	free(l2);
	free(line);
	return (cam);
}

void	cam_parse(t_env *e, int type, int fd)
{
	t_cam	*save;

	(void)type;
	save = e->s.cams;
	if (save != NULL)
	{
		while(save->next != NULL)
			save = save->next;
		save->next = cam_parse_2(e, fd);
	}
	else
		e->s.cams = cam_parse_2(e, fd);
}
