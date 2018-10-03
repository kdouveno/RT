/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 19:06:10 by gperez            #+#    #+#             */
/*   Updated: 2017/11/12 17:52:49 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa_sub(int n, int lng, int signe, char *resultat)
{
	int		cmpt;

	cmpt = 0;
	if (signe < 0)
	{
		resultat[cmpt] = '-';
		cmpt++;
		lng--;
	}
	lng = (ft_pow(10, lng - 1));
	while (lng > 0)
	{
		resultat[cmpt] = ((long)n * -1) / lng + '0';
		n %= lng;
		lng /= 10;
		cmpt++;
	}
	resultat[cmpt] = '\0';
	return (resultat);
}

char		*ft_itoa(int n)
{
	char	*resultat;
	int		nb_clone;
	int		lng;
	int		signe;

	signe = 1;
	lng = 0;
	if (n == 0)
		lng = 1;
	if (n < 0)
	{
		signe = -1;
		lng++;
	}
	else
		n *= -1;
	nb_clone = n;
	while (nb_clone < 0)
	{
		nb_clone /= 10;
		lng++;
	}
	if (!(resultat = (char *)malloc(sizeof(char) * lng + 1)))
		return (NULL);
	return (ft_itoa_sub(n, lng, signe, resultat));
}
