/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_hexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 18:17:07 by gperez            #+#    #+#             */
/*   Updated: 2018/10/25 18:34:44 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		hexa_dic(char h)
{
	int		i;

	i = 0;
	while (g_hexa[i].hexa && g_hexa[i].hexa != h)
		i++;
	return (g_hexa[i].n);
}

int		atoi_hexa(char const *str)
{
	long	n;
	int		i;
	int		len;

	len = strlen(str) - 1;
	if (len > 6)
		len = 6;
	n = 0;
	i = 0;
	while (str[i] && i < 6)
	{
		n += hexa_dic(str[i]) * pow(16, len);
		len--;
		i++;
	}
	return (n);
}
