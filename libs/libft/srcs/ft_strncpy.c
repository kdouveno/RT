/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 09:48:20 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/20 14:09:19 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	int		fill;

	i = 0;
	fill = 0;
	while (i < n)
	{
		if (!src[i])
			fill = 1;
		if (fill)
			dest[i] = '\0';
		else
			dest[i] = src[i];
		i++;
	}
	return (dest);
}
