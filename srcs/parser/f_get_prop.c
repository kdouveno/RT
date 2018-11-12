/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_get_prop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:35:31 by gperez            #+#    #+#             */
/*   Updated: 2018/11/12 17:17:47 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	get_prop2(char *line, char *l1, char *l2, int trio[3])
{
	int i;
	int j;

	i = 0;
	j = 0;
	trio[2] = 0;
	while (line[i])
	{
		if (is_name_char(line[i]))
		{
			if (trio[2])
				l2[j] = line[i];
			else
				l1[j] = line[i];
			j++;
		}
		else if (line[i] == ':')
		{
			trio[2] = 1;
			j = 0;
		}
		i++;
	}
	l1[trio[0]] = '\0';
	l2[trio[1]] = '\0';
}

int			get_prop(t_env *e, char *line, char **l1, char **l2)
{
	int i;
	int	trio[3];

	i = 0;
	trio[0] = 0;
	trio[1] = 0;
	trio[2] = 0;
	while (line[i])
	{
		if (is_name_char(line[i]))
			trio[0 + trio[2]]++;
		else if (line[i] == ':')
			trio[2] = 1;
		else if (line[i] == '}')
			return (1);
		i++;
	}
	if ((!trio[0] || !trio[1]) && (trio[2] || trio[0]))
		wrong_type(e, line, 0, 0);
	if (!(*l1 = (char*)malloc(sizeof(char) * (trio[0] + 1)))
	|| !(*l2 = (char*)malloc(sizeof(char) * (trio[1] + 1))))
		error(e, MALLOC_ERROR);
	get_prop2(line, *l1, *l2, trio);
	return (0);
}
