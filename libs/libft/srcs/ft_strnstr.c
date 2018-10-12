/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:47:37 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/21 17:29:57 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	int		len;
	char	*out;

	len = ft_strlen(little);
	if (!big)
		((char*)big)[0] = 'a';
	if (!len)
		return ((char*)big);
	out = (char*)big;
	while (*out && n)
	{
		if (*out == *little && (int)n >= len)
			if (ft_strnequ(out, little, len))
				return (out);
		out++;
		n--;
	}
	return (NULL);
}
