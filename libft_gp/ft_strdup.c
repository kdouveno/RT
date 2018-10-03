/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:15:26 by gperez            #+#    #+#             */
/*   Updated: 2017/11/12 20:56:05 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *s1)
{
	int		cmpt;
	char	*dst;

	if (!(dst = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1)))
		return (NULL);
	cmpt = 0;
	while (s1[cmpt])
	{
		dst[cmpt] = s1[cmpt];
		cmpt++;
	}
	dst[cmpt] = '\0';
	return (dst);
}
