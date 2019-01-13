/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse_grad.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:15:27 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/13 15:05:22 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		check_arg(t_env *e, t_grad *grad, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "dir")))
		parse_3d(e, &grad->r, l2);
	else if (!(ft_strcmp(l1, "id")))
	{
		grad->id = ft_atoi(l2);
		grad->id = grad->id < 0 ? -grad->id : grad->id;
	}
	else if (!(ft_strcmp(l1, "c1")) || !(ft_strcmp(l1, "color1")))
		parse_color(NULL, l2, grad, 1);
	else if (!(ft_strcmp(l1, "c2")) || !(ft_strcmp(l1, "color2")))
		parse_color(NULL, l2, grad, 2);
	else
		return (1);
	return (0);
}

void			stock_grad(t_env *e, t_grad *grad, char *l1, char *l2)
{
	char	*cp;
	int		i;

	i = 0;
	cp = ft_str_tolower(l1);
	if (!cp)
		error(e, MALLOC_ERROR);
	if (check_loc(e, grad, cp, l2) && check_pt(grad, cp, l2)
	&& check_arg(e, grad, cp, l2) && check_dir(grad, cp, l2))
	{
		while (is_ignored(l1[i]))
			i++;
		if (l1[i] != '\0')
			wrong_type(e, l1, 0, 0);
	}
	ft_memdel((void**)&cp);
}

t_grad			*parse_grad_2(t_env *e, int fd)
{
	char	*line;
	int		res;
	char	*l1;
	char	*l2;
	t_grad	*grad;

	if (!(grad = malloc(sizeof(t_grad))))
		error(e, MALLOC_ERROR);
	*grad = (t_grad){NULL, zero_matrix(), -1, {}, {},
		(t_color)(unsigned)0, (t_color)(unsigned)0, {0, 0, 0, 0}};
	while ((res = get_next_line(fd, &line)) > 0
		&& get_prop(e, line, &l1, &l2) != 1)
	{
		stock_grad(e, grad, l1, l2);
		ft_memdel((void**)&l1);
		ft_memdel((void**)&l2);
		ft_memdel((void**)&line);
		if (res == -1)
			error(e, READ_ERROR);
	}
	ft_memdel((void**)&line);
	return (grad);
}

void			parse_grad(t_env *e, int type, int fd, t_scene *s)
{
	t_grad	*save;

	(void)type;
	save = s->grads;
	if (save != NULL)
	{
		while(save->next != NULL)
			save = save->next;
		save->next = parse_grad_2(e, fd);
	}
	else
		s->grads = parse_grad_2(e, fd);
}
