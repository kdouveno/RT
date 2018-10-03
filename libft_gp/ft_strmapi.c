/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 20:35:57 by gperez            #+#    #+#             */
/*   Updated: 2017/11/23 14:39:15 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		cmpt;
	char	*dst;

	if (s)
	{
		cmpt = 0;
		if ((dst = ft_strdup(s)) == NULL)
			return (NULL);
		while (s[cmpt])
		{
			dst[cmpt] = (*f)(cmpt, s[cmpt]);
			cmpt++;
		}
		return (dst);
	}
	return (NULL);
}
