/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 16:11:35 by gperez            #+#    #+#             */
/*   Updated: 2017/11/19 15:55:37 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	cmpt;

	cmpt = 0;
	if (n == 0)
		return (0);
	while (cmpt < n)
	{
		if (((unsigned char *)s1)[cmpt] != ((unsigned char *)s2)[cmpt])
			return (((unsigned char *)s1)[cmpt] - ((unsigned char *)s2)[cmpt]);
		cmpt++;
	}
	return (0);
}
