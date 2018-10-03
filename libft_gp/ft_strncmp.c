/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:00:22 by gperez            #+#    #+#             */
/*   Updated: 2017/11/23 23:40:35 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(char const *s1, char const *s2, size_t n)
{
	int		cmpt;

	cmpt = 0;
	if (n == 0)
		return (0);
	while (s1[cmpt] && cmpt < ((int)n - 1))
	{
		if (s1[cmpt] != s2[cmpt])
			return (((unsigned char *)s1)[cmpt] - ((unsigned char *)s2)[cmpt]);
		cmpt++;
	}
	return (((unsigned char *)s1)[cmpt] - ((unsigned char *)s2)[cmpt]);
}
