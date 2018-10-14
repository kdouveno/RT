/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:46:14 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/21 16:35:27 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t		i;

	i = 0;
	if (n == 0)
		return (NULL);
	while (i < n && (i == 0
				|| ((unsigned char*)src)[i - 1] != (unsigned char)c))
	{
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
		i++;
	}
	return (((unsigned char*)dest)[i - 1] == (unsigned char)c ?
			&(((unsigned char*)dest)[i]) : NULL);
}
