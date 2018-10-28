/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prst_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 18:54:01 by gperez            #+#    #+#             */
/*   Updated: 2018/10/28 19:47:09 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		check_arg(t_env *e, t_obj *obj, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "src")))
 	{
 		if (check_file_ext(l2, ".rt") && l2[0])
 			wrong_type(e, l1, 0, 0);
 		else if (l2[0])
 			parse(e, ft_strjoin("file/", l2), 1);
 		return (0);
 	}
	return (1);
}

void	stock_prst(t_env *e, t_prst *prst, char *l1, char *l2)
{
	char	*cp;
	int		i;

	i = 0;
	cp = ft_str_tolower(l1);
	if (check_pt(prst, cp, l2) == 1 && check_rot(prst, cp, l2) == 1
			&& check_arg(prst, cp, l2) == 1)
	{
		while (is_ignored(l1[i]) == 1)
			i++;
		if (l1[i] != '\0')
			wrong_type(e, l1, 0, 0);
	}
	ft_memdel((void**)&cp);
}

t_prst	*prst_parse_2(t_env *e, int type, int fd)
{
	char	*line;
	int		res;
	char	*l1;
	char	*l2;
	t_prst	*prst;

	if (!(prst = malloc(sizeof(t_prst))))
		error(e, MALLOC_ERROR);
	*prst = (t_prst){{0, 0, 0}, {0, 0, 0}, NULL, NULL, NULL, NULL};
	while ((res = get_next_line(fd, &line)) > 0
		&& get_prop(e, line, &l1, &l2) != 1)
	{
		stock_prst(e, prst, l1, l2);
		ft_memdel((void**)&l1);
		ft_memdel((void**)&l2);
		ft_memdel((void**)&line);
		if (res == -1)
			error(e, READ_ERROR);
	}
	ft_memdel((void**)&line);
	return (prst);
}


void	prst_parse(t_env *e, int type, int fd)
{
	t_prst	*save;

	save = e->p;
	if (save != NULL)
	{
		while(save->next != NULL)
			save = save->next;
		save->next = prst_parse_2(e, type, fd);
	}
	else
		e->p = prst_parse_2(e, type, fd);
}
