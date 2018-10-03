/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:33:40 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/21 17:21:01 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		len;
	char	*end;
	char	*start;
	int		i;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while (SP_C(s[i]))
		i++;
	if (!s[i])
		return (ft_strnew(0));
	start = (char*)s + i;
	i = len - 1;
	while (i >= 0 && SP_C(s[i]))
		i--;
	end = (char*)s + i + 1;
	return (ft_strsub(start, 0, (size_t)(end - start)));
}
