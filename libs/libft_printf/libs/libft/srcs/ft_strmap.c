/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 11:44:56 by kdouveno          #+#    #+#             */
/*   Updated: 2018/01/08 15:33:30 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*out;
	int		i;
	int		len;

	if (s == NULL || *s == '\0')
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	if (!(out = ft_strnew(len)))
		return (NULL);
	while (i < len)
	{
		out[i] = f(s[i]);
		i++;
	}
	return (out);
}
