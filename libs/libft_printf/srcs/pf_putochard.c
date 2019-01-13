/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putochard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:22:04 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:22:12 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_pochard(unsigned char nbr, t_params *pa)
{
	pa->width--;
	pa->precision--;
	if ((nbr / pa->base || (pa->precision > 0)
	|| (pa->zero && pa->width > 0)))
		pf_pochard(nbr / (unsigned char)pa->base, pa);
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

void		pf_putochard(va_list p, t_params *pa)
{
	unsigned char	nbr;

	pa->width -= 1;
	pa->base = 8;
	if (pa->left || pa->precision != -1)
		pa->zero = 0;
	if (pa->hash == 1)
		pa->width--;
	nbr = (unsigned char)va_arg(p, unsigned int);
	if ((nbr > 0 && !pa->pos) || nbr == 0)
		pa->width++;
	if (pa->precision != 0 || nbr != 0 || pa->hash)
	{
		if (pa->hash && !nbr)
		{
			pa->hash = 0;
			pa->width++;
		}
		pf_pochard(nbr, pa);
	}
	else
		pa->left = 1;
	if (pa->left)
		pf_spaces(pa->width);
}
