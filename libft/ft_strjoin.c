/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:35:40 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/21 17:16:20 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *out;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(out = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	if (!out)
		return (NULL);
	ft_strcpy(out, s1);
	ft_strcpy(out + ft_strlen(s1), s2);
	return (out);
}
