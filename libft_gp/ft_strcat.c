/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 09:07:27 by gperez            #+#    #+#             */
/*   Updated: 2017/11/21 16:53:45 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, char const *s2)
{
	size_t		cmpt_s1;
	size_t		cmpt_s2;

	cmpt_s1 = 0;
	cmpt_s2 = 0;
	while (cmpt_s1 < ft_strlen(s1))
	{
		cmpt_s1++;
	}
	while (s2[cmpt_s2])
	{
		s1[cmpt_s1] = s2[cmpt_s2];
		cmpt_s1++;
		cmpt_s2++;
	}
	s1[cmpt_s1] = '\0';
	return (s1);
}
