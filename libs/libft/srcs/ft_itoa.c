/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 10:41:19 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/16 16:11:54 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_itoa_write(char *out, int n)
{
	*out = n % 10 + 48;
	if (n / 10)
		ft_itoa_write(out - 1, n / 10);
}

char			*ft_itoa(int n)
{
	int		len;
	int		nbr;
	char	*out;

	if (n == -2147483648)
	{
		if (!(out = ft_strnew(12)))
			return (NULL);
		ft_strcpy(out, "-2147483648");
		return (out);
	}
	nbr = n;
	len = n < 0 ? 2 : 1;
	while (nbr / 10)
	{
		nbr /= 10;
		len++;
	}
	if (!(out = ft_strnew(len)))
		return (NULL);
	*out = n < 0 ? '-' : *out;
	n = ABS(n);
	ft_itoa_write(out + len - 1, n);
	return (out);
}
