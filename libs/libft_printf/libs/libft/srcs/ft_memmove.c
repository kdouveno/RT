/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:46:28 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/21 13:24:36 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memcpy_rev(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*out;

	out = (char*)dst;
	if (len == 0)
		return (out);
	i = len - 1;
	while (i > 0)
	{
		out[i] = ((char*)src)[i];
		i--;
	}
	if (i == 0)
		out[i] = ((char*)src)[i];
	return ((char*)out);
}

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst == src)
		return (dst);
	if (dst > src)
		return (ft_memcpy_rev(dst, src, len));
	return (ft_memcpy(dst, src, len));
}
