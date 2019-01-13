/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putulong.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:23:02 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:23:03 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_pulong(unsigned long nbr, t_params *pa)
{
	pa->width--;
	pa->precision--;
	if ((nbr / pa->base || (pa->precision > 0)
	|| (pa->zero && pa->width > 0)))
		pf_pulong(nbr / (unsigned long)pa->base, pa);
	else
	{
		if (!pa->zero && !pa->left)
			pf_spaces(pa->width);
		pf_prefix(pa);
	}
	pc_putchar(nbr % pa->base + 48);
}

void		pf_putulong(va_list p, t_params *pa)
{
	unsigned long nbr;

	pa->pos = 0;
	if (pa->left || pa->precision != -1)
		pa->zero = 0;
	nbr = va_arg(p, unsigned long);
	if (pa->precision != 0 || nbr != 0)
		pf_pulong(nbr, pa);
	else
		pa->left = 1;
	if (pa->left)
		pf_spaces(pa->width);
}
