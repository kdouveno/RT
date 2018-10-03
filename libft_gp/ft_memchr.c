/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 16:58:20 by gperez            #+#    #+#             */
/*   Updated: 2017/11/23 21:58:48 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t cmpt;

	cmpt = 0;
	while (cmpt < n)
	{
		if (((unsigned char *)s)[cmpt] == (unsigned char)c)
			return (((unsigned char *)s) + cmpt);
		cmpt++;
	}
	return (NULL);
}
