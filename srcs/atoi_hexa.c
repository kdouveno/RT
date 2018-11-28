/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_hexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 18:17:07 by gperez            #+#    #+#             */
/*   Updated: 2018/11/20 17:49:44 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		hexa_dic(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	return (0);
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
