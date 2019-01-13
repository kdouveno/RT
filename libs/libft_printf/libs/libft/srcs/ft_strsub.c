/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:01:35 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/21 17:15:43 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *out;

	if (s == NULL)
		return (NULL);
	if (!(out = ft_strnew(len)))
		return (NULL);
	ft_strncpy(out, s + start, len);
	return (out);
}
