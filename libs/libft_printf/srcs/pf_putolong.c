/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putolong.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:22:27 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:22:27 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_polong(unsigned long nbr, t_params *pa)
{
	pa->width--;
	pa->precision--;
	if ((nbr / pa->base || (pa->precision > 0)
	|| (pa->zero && pa->width > 0)))
		pf_polong(nbr / (unsigned long)pa->base, pa);
	else
	{
		if (!pa->zero && !pa->left)
			pf_spaces(pa->width);
		if (!(nbr % pa->base))
			pa->hash = 0;
		pf_prefix(pa);
	}
	pc_putchar(nbr % pa->base + 48);
}

void		pf_putolong(va_list p, t_params *pa)
{
	unsigned long nbr;

	pa->width -= 1;
	pa->base = 8;
	if (pa->left || pa->precision != -1)
		pa->zero = 0;
	if (pa->hash == 1)
		pa->width--;
	nbr = va_arg(p, unsigned long);
	if ((nbr > 0 && !pa->pos) || nbr == 0)
		pa->width++;
	if (pa->precision != 0 || nbr != 0 || pa->hash)
	{
		if (pa->hash && !nbr)
		{
			pa->hash = 0;
			pa->width++;
		}
		pf_polong(nbr, pa);
	}
	else
		pa->left = 1;
	if (pa->left)
		pf_spaces(pa->width);
}
