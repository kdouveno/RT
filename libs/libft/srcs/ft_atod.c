/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:41:13 by kdouveno          #+#    #+#             */
/*   Updated: 2018/05/16 13:51:46 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

double		ft_atod(const char *str)
{
	int		i;
	long	c;
	double	out;
	int		bools;

	out = 0;
	c = 10;
	bools = (str[0] == '-');
	i = bools;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			out += str[i] - 48;
			out *= 10;
		}
		if (str[i] == '.' && !(bools & 2))
			bools |= 2;
		else if (!ft_isdigit(str[i]))
			break ;
		else if (bools & 2)
			c *= 10;
		i++;
	}
	return (out / c * (bools & 1 ? -1 : 1));
}
