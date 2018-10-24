/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:55:48 by kdouveno          #+#    #+#             */
/*   Updated: 2018/10/23 16:28:58 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	exachar(char c)
{
	int i;

	i = 0;
	if (c >= 'a' && c <= 'f')
		c -= 32;
	else if (c >= 'A' && c <= 'F')
		c -= 16;
	while (g_exachar[i])
	{
		if (g_exachar[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int			ft_extoi(const char *str)
{
	int	i;
	int	nb;
	int	neg;

	i = 0;
	nb = 0;
	neg = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r') ||
		str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		if ((str[i] == '+' || str[i] == '-') &&
			exachar(str[i + 1]) == -1)
			return (0);
		i++;
	}
	while (exachar(str[i]) >= 0)
	{
		nb = (nb * 16) + exachar(str[i]);
		i++;
	}
	return (nb * neg);
}
