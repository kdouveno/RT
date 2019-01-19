/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 21:38:47 by gperez            #+#    #+#             */
/*   Updated: 2019/01/19 14:25:05 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puttab_s(char **tab, int space)
{
	int		cmpt;

	cmpt = 0;
	while (tab[cmpt] != NULL)
	{
		if (space == 1)
			ft_putendl(tab[cmpt]);
		else
			ft_putstr(tab[cmpt]);
		cmpt++;
	}
}
