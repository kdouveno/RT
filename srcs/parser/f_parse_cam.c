/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse_cam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:49:52 by gperez            #+#    #+#             */
/*   Updated: 2019/01/18 16:49:34 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		check_dimx_dimy(t_cam *cam, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "dimx")))
		cam->data.dimx = ft_atoi(l2) < 0 ? -ft_atoi(l2) : ft_atoi(l2);
	else if (!(ft_strcmp(l1, "dimy")))
		cam->data.dimy = ft_atoi(l2) < 0 ? -ft_atoi(l2) : ft_atoi(l2);
	else if (!(ft_strcmp(l1, "filter")))
	{
		if (!(ft_strcmp(l2, "black")))
			cam->data.filter = 'b';
		if (!(ft_strcmp(l2, "sepia")))
			cam->data.filter = 's';
	}
	else if (!(ft_strcmp(l1, "aaa")))
		cam->data.aaa = 0;
	else if (!(ft_strcmp(l1, "para")))
		cam->data.para = 1;
	else
		return (1);
	return (0);
}

static int		check_arg(t_cam *cam, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "id")))
	{
		cam->id = ft_atoi(l2);
		cam->id = cam->id < 0 ? -cam->id : cam->id;
	}
	else if (!(ft_strcmp(l1, "fov")))
	{
		cam->data.fov = ft_atod(l2);
		cam->data.fov = cam->data.fov < 0 ? -cam->data.fov : cam->data.fov;
	}
	else if (!(ft_strcmp(l1, "ssaa")))
	{
		cam->data.ssaa = ft_atoi(l2);
		cam->data.ssaa = cam->data.ssaa < 0 ? -cam->data.ssaa : cam->data.ssaa;
		if (!(is_alia(cam->data.ssaa)) && cam->data.ssaa != 1)
		{
			cam->data.ssaa = 1;
			ft_putstr("\033[2;49;91mssaa is invalid -> changed to 1\n");
		}
	}
	else
		return (1);
	return (0);
}

void			stock_cam(t_env *e, t_cam *cam, char *l1, char *l2)
{
	char	*cp;
	int		i;

	i = 0;
	cp = ft_str_tolower(l1);
	if (check_loc(e, cam, cp, l2) && check_pt(cam, cp, l2)
		&& check_rot(cam, cp, l2) && check_arg(cam, cp, l2)
		&& check_dir(cam, cp, l2) && check_dimx_dimy(cam, cp, l2))
	{
		while (is_ignored(l1[i]) == 1)
			i++;
		if (l1[i] != '\0')
			wrong_type(e, l1, 0, 0);
	}
	ft_memdel((void**)&cp);
}

t_cam			*parse_cam_2(t_env *e, int fd)
{
	char	*line;
	int		res;
	char	*l1;
	char	*l2;
	t_cam	*cam;

	if (!(cam = ft_memalloc(sizeof(t_cam))))
		error(e, MALLOC_ERROR);
	*cam = (t_cam){NULL, zero_matrix(), -1,
		{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, FOV, NULL, 0,
		0, DIMX, DIMY, 1, 1, 0, '\0'}};
	while ((res = get_next_line(fd, &line)) > 0
		&& get_prop(e, line, &l1, &l2) != 1)
	{
		stock_cam(e, cam, l1, l2);
		ft_memdel((void**)&l1);
		ft_memdel((void**)&l2);
		ft_memdel((void**)&line);
		if (res == -1)
			error(e, READ_ERROR);
	}
	ft_memdel((void**)&line);
	return (cam);
}

void			parse_cam(t_env *e, int type, int fd, t_scene *s)
{
	t_cam	*save;

	(void)type;
	save = s->cams;
	if (save != NULL)
	{
		while (save->next != NULL)
			save = save->next;
		save->next = parse_cam_2(e, fd);
	}
	else
		s->cams = parse_cam_2(e, fd);
}
