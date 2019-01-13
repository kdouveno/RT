/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putxlong.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:23:29 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:23:30 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_pxlong(unsigned long nbr, t_params *pa)
{
	pa->width--;
	pa->precision--;
	if ((nbr / pa->base || (pa->precision > 0)
	|| (pa->zero && pa->width > 0)))
		pf_pxlong(nbr / (unsigned long)pa->base, pa);
	else
	{
		if (!pa->zero && !pa->left)
			pf_spaces(pa->width);
		pf_prefix(pa);
	}
	if (pa->pos == 80)
		pc_putchar(nbr % pa->base + (nbr % pa->base > 9 ? 55 : 48));
	else
		pc_putchar(nbr % pa->base + (nbr % pa->base > 9 ? 87 : 48));
}

void		pf_putxlong(va_list p, t_params *pa)
{
	unsigned long nbr;

	pa->base = 16;
	if (pa->pos != 80)
		pa->pos = 0;
	if (pa->left || pa->precision != -1)
		pa->zero = 0;
	if (pa->hash == 1)
		pa->width -= 2;
	nbr = va_arg(p, unsigned long);
	if (pa->hash && !nbr)
		pa->width += 2;
	if (pa->precision != 0 || nbr != 0)
	{
		if (pa->hash && !nbr)
			pa->hash = 0;
		pf_pxlong(nbr, pa);
	}
	else
		pa->left = 1;
	if (pa->left)
		pf_spaces(pa->width);
}
