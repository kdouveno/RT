/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 11:52:02 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/21 17:11:04 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*out;
	int		i;
	int		len;

	if (s == NULL || *s == '\0' || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	if (!(out = ft_strnew(len)))
		return (NULL);
	while (i < len)
	{
		out[i] = f(i, s[i]);
		i++;
	}
	return (out);
}
