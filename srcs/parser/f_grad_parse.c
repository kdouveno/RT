/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_deg_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:15:27 by kdouveno          #+#    #+#             */
/*   Updated: 2018/10/15 14:17:13 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		check_arg(t_grad *grad, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "id")))
	{
		grad->id = ft_strdup(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "color1")))
	{
		grad->color1 = (t_color)ft_atoi(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "color2")))
	{
		grad->color2 = (t_color)ft_atoi(l2);
		return (0);
	}
	return (1);
}

void			stock_grad(t_env *e, t_grad *grad, char *l1, char *l2)
{
	char	*cp;
	int		i;

	i = 0;
	cp = ft_str_tolower(l1);
	if (check_pt(grad, cp, l2) == 1 && check_arg(grad, cp, l2) == 1
	 && check_rot(grad, cp, l2) == 1)
	{
		while (is_ignored(l1[i]) == 1)
			i++;
		if (l1[i] != '\0')
			wrong_type(e, l1, 0, 0);
	}
	free(cp);
}

t_grad			*grad_parse_2(t_env *e, int fd)
{
	char	*line;
	int		res;
	char	*l1;
	char	*l2;
	t_grad	*grad;

	if (!(grad = malloc(sizeof(t_grad))))
		error(e, MALLOC_ERROR);
	*grad = (t_grad){(t_pt){0, 0, 0}, (t_vec){0, 0, 0}, NULL, (t_color)0, (t_color)0, NULL};
	while ((res = get_next_line(fd, &line)) > 0
		&& get_prop(e, line, &l1, &l2) != 1)
	{
		stock_grad(e, grad, l1, l2);
		free(line);
		if (res == -1)
			error(e, READ_ERROR);
	}
	free(l1);
	free(l2);
	free(line);
	return (grad);
}

void			grad_parse(t_env *e, int type, int fd)
{
	t_grad	*save;

	(void)type;
	save = e->s.grads;
	if (save != NULL)
	{
		while(save->next != NULL)
			save = save->next;
		save->next = grad_parse_2(e, fd);
	}
	else
		e->s.grads = grad_parse_2(e, fd);
}
