/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse_loc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 11:12:40 by kdouveno          #+#    #+#             */
/*   Updated: 2018/12/21 16:52:52 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	free_tab(char **tab)
{
	while (tab)
		free(*(tab++));
	free(tab);
}

int		parse_3d(t_env *e, t_pt *pt, char *l2)
{
	char	**tab;
	int 	i;
	t_pt	tmp;

	if (!(tab = ft_strsplit(l2, ',')))
		error(e, MALLOC_ERROR);
	i = 0;
	while (tab[i])
	{
		*((double*)&tmp + i) = tab[i][0] != '~' ?
		ft_atod(tab[i]) : *((double*)pt + i);
		i++;
	}
	free(tab);
	if (i == 3)
	{
		*pt = tmp;
		return (0);
	}
	return (1);
}

void	parse_loc(t_env *e, t_obj *o, char *l2)
{
	if (parse_3d(e, &o->m.pt, l2))
		o->m.l.id = ft_atoi(l2);
}
