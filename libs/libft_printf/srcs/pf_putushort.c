/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putushort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:23:09 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:23:10 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_pushort(unsigned short nbr, t_params *pa)
{
	pa->width--;
	pa->precision--;
	if ((nbr / pa->base || (pa->precision > 0)
	|| (pa->zero && pa->width > 0)))
		pf_pushort(nbr / (unsigned short)pa->base, pa);
	else
	{
		if (!pa->zero && !pa->left)
			pf_spaces(pa->width);
		pf_prefix(pa);
	}
	pc_putchar(nbr % pa->base + 48);
}

void		pf_putushort(va_list p, t_params *pa)
{
	unsigned short	nbr;

	pa->pos = 0;
	if (pa->left || pa->precision != -1)
		pa->zero = 0;
	nbr = (unsigned short)va_arg(p, int);
	if (pa->precision != 0 || nbr != 0)
		pf_pushort(nbr, pa);
	else
		pa->left = 1;
	if (pa->left)
		pf_spaces(pa->width);
}
