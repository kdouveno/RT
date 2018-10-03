/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:07:28 by gperez            #+#    #+#             */
/*   Updated: 2017/11/13 11:35:20 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, char const *src)
{
	int		cmpt;

	cmpt = 0;
	while (src[cmpt] != '\0')
	{
		dst[cmpt] = src[cmpt];
		cmpt++;
	}
	dst[cmpt] = '\0';
	return (dst);
}
