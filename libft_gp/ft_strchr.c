/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 12:31:55 by gperez            #+#    #+#             */
/*   Updated: 2017/11/19 16:39:13 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char const *s, int c)
{
	int		cmpt;

	cmpt = 0;
	while (s[cmpt])
	{
		if (s[cmpt] == c)
			return ((char *)s + cmpt);
		cmpt++;
	}
	if (c == '\0')
		return ((char *)s + cmpt);
	return (NULL);
}
