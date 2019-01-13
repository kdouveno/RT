/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 09:48:29 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/16 12:39:43 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	int		len;

	len = ft_strlen(str);
	i = 1;
	while (len - i >= 0)
	{
		if (str[len - i] == c)
			return ((char *)&(str[len - i]));
		i++;
	}
	return (c ? NULL : (char*)&(str[len]));
}
