/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_tolower.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 06:43:16 by gperez            #+#    #+#             */
/*   Updated: 2017/11/24 08:00:24 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_tolower(char *s)
{
	int		cmpt;
	char	*s2;

	s2 = ft_strdup(s);
	if (s)
	{
		cmpt = 0;
		while (s[cmpt])
		{
			s2[cmpt] = ft_tolower(s[cmpt]);
			cmpt++;
		}
		return (s2);
	}
	return (NULL);
}
