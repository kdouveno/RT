/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:45:31 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/20 14:07:05 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*out;

	out = (char*)dst;
	i = 0;
	while (i < n)
	{
		out[i] = ((char*)src)[i];
		i++;
	}
	return (void*)out;
}
