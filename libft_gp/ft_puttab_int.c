/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 12:12:38 by gperez            #+#    #+#             */
/*   Updated: 2018/02/13 18:51:24 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puttab_int(int *tab, int taille, int space)
{
	int		cmpt;

	cmpt = 0;
	while (cmpt < taille)
	{
		ft_putnbr(tab[cmpt]);
		if (space == 1)
			ft_putchar('\n');
		cmpt++;
	}
}
