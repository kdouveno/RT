/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putullong.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:22:58 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:22:59 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_pullong(unsigned long long nbr, t_params *pa)
{
	pa->width--;
	pa->precision--;
	if ((nbr / pa->base || (pa->precision > 0)
	|| (pa->zero && pa->width > 0)))
		pf_pullong(nbr / (unsigned long long)pa->base, pa);
	else
	{
		if (!pa->zero && !pa->left)
			pf_spaces(pa->width);
		pf_prefix(pa);
	}
	pc_putchar(nbr % pa->base + 48);
}

void		pf_putullong(va_list p, t_params *pa)
{
	unsigned long long nbr;

	pa->pos = 0;
	if (pa->left || pa->precision != -1)
		pa->zero = 0;
	nbr = va_arg(p, unsigned long long);
	if (pa->precision != 0 || nbr != 0)
		pf_pullong(nbr, pa);
	else
		pa->left = 1;
	if (pa->left)
		pf_spaces(pa->width);
}
