/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 09:48:35 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/20 11:17:09 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int u;

	u = 0;
	i = 0;
	if (!*needle)
		return ((char*)haystack);
	while (haystack[i] != '\0')
	{
		u = 0;
		while (needle[u] == haystack[i + u])
		{
			u++;
			if (needle[u] == '\0')
				return (&((char*)haystack)[i]);
		}
		i++;
	}
	return (0);
}
