/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:08:17 by gperez            #+#    #+#             */
/*   Updated: 2017/11/20 00:13:00 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static int	ft_atoi_s(char const *str, int cmpt, int signe)
{
	long	resultat;

	resultat = 0;
	while (str[cmpt] != '\0')
	{
		if (str[cmpt] < '0' || str[cmpt] > '9')
			return (resultat * -signe);
		resultat -= (str[cmpt] - '0');
		if (str[cmpt + 1] >= '0' && str[cmpt + 1] <= '9')
			resultat *= 10;
		cmpt++;
	}
	return ((int)resultat * -signe);
}

int			ft_atoi(char const *str)
{
	int		cmpt;
	int		signe;

	cmpt = 0;
	signe = 1;
	while (str[cmpt] == ' ' || str[cmpt] == '\r' || str[cmpt] == '\v' ||
	str[cmpt] == '\f' || str[cmpt] == '\t' || str[cmpt] == '\n')
		cmpt++;
	if ((str[cmpt] >= '0' && str[cmpt] <= '9') || str[cmpt] == '+'
	|| str[cmpt] == '-')
	{
		if (str[cmpt] == '+' || str[cmpt] == '-')
		{
			if (str[cmpt] == '-')
				signe = -1;
			cmpt++;
		}
		return (ft_atoi_s(str, cmpt, signe));
	}
	else
		return (0);
}
