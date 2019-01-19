/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_check_ext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:17:56 by gperez            #+#    #+#             */
/*   Updated: 2019/01/11 15:25:02 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_file_ext(const char *str, const char *ext)
{
	int	len;

	len = ft_strlen(str);
	if (len > (int)ft_strlen(ext))
	{
		if (!(ft_strcmp(&(str[len - ft_strlen(ext)]), ext)))
			return (0);
		else
			return (1);
	}
	return (1);
}

void	check_last(const char *str, int *p_c, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			*p_c = i;
		i++;
	}
}

char	*file_name(char *str)
{
	int		len;
	char	*out;
	char	*name;
	int		i;
	int		last;

	check_last(str, &last, '/');
	name = str;
	len = ft_strlen(name);
	out = NULL;
	if (len > 4)
	{
		if (!(out = ft_memalloc(sizeof(char) * len - last - 4 + 1)))
			return (NULL);
		i = 0;
		while (last + 1 < len - 4)
		{
			out[i] = name[last + 1];
			last++;
			i++;
		}
		out[i] = '\0';
	}
	return (out);
}
