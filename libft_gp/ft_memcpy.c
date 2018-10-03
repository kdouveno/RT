/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 20:03:26 by gperez            #+#    #+#             */
/*   Updated: 2017/11/17 16:09:12 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	cmpt;

	cmpt = 0;
	while (cmpt < n)
	{
		((char *)dst)[cmpt] = ((char *)src)[cmpt];
		cmpt++;
	}
	return (dst);
}
