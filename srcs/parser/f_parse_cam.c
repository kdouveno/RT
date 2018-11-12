/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse_cam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:49:52 by gperez            #+#    #+#             */
/*   Updated: 2018/11/12 17:18:02 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		is_pos(int nb)
{
	if (nb > 0)
		return (1);
	return (0);
}

static int		is_powertwo(int nb)
{
	int	cp;

	cp = sqrt(nb);
	if (nb == 0)
		return (0);
	if (nb == 2)
		return (1);
	if (cp * cp == nb)
		return (1);
	return (0);
}

static int check_dimx_dimy(t_cam *cam, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "dimx")))
	{
		cam->data.dimx = ft_atoi(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "dimy")))
	{
		cam->data.dimy = ft_atoi(l2);
		return (0);
	}
	return (1);
}

static int		check_arg(t_cam *cam, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "id")))
	{
		cam->id = ft_atoi(l2);
		cam->id = cam->id < 0 ? -cam->id : cam->id;
		return (0);
	}
	else if (!(ft_strcmp(l1, "fov")))
	{
		cam->data.fov = rad(ft_atoi(l2));
		cam->data.fov = cam->data.fov < 0 ? -cam->data.fov : cam->data.fov;
		return (0);
	}
	else if (!(ft_strcmp(l1, "antialiasing")))
	{
		if (!(is_powertwo(cam->data.antialia)) && !(is_pos(cam->data.antialia)))
		{
			cam->data.antialia = 1;
			ft_putstr("\033[2;49;91mAntialiasing is not a power of 2 -> changed to 1\n");
		}
		return (0);
	}
	return(1);
}

void	stock_cam(t_env *e, t_cam *cam, char *l1, char *l2)
{
	char	*cp;
	int		i;

	i = 0;
	cp = ft_str_tolower(l1);
	if (check_pt(cam, cp, l2) == 1 && check_rot(cam, cp, l2) == 1
		&& check_arg(cam, cp, l2 ) == 1 && check_dir(cam, cp, l2) == 1
		&& check_dimx_dimy(cam, cp, l2) == 1)
	{
		while (is_ignored(l1[i]) == 1)
			i++;
		if (l1[i] != '\0')
			wrong_type(e, l1, 0, 0);
	}
	ft_memdel((void**)&cp);
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
	*cam = (t_cam){(t_pt){0, 0, 0},(t_vec){0, 0, 0}, -1, -1,
		{{0,0,0}, {}, {}, rad(FOV), NULL, 0, 0, 0, 0, 0, 0, 1},
		NULL};
	while ((res = get_next_line(fd, &line)) > 0 &&
		get_prop(e, line, &l1, &l2) != 1)
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

void	cam_parse(t_env *e, int type, int fd, t_scene *s)
{
	t_cam	*save;

	(void)type;
	save = s->cams;
	if (save != NULL)
	{
		while(save->next != NULL)
			save = save->next;
		save->next = cam_parse_2(e, fd);
	}
	else
		s->cams = cam_parse_2(e, fd);
}
