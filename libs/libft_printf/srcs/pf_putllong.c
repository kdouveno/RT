/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putllong.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:21:55 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:21:56 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_pllong(long long nbr, t_params *pa)
{
	long long	min;

	if ((min = (nbr == min_ll())))
	{
		pa->neg = 1;
		pf_pllong((nbr - 1) / pa->base, pa);
	}
	if (nbr < 0)
	{
		nbr = min ? nbr - 1 : -nbr;
		pa->neg = min ? pa->neg : 1;
	}
	pa->width--;
	pa->precision--;
	if ((nbr / pa->base || (pa->precision > 0)
	|| (pa->zero && pa->width > 0)) && !min)
		pf_pllong(nbr / (long long)pa->base, pa);
	else if (!min)
	{
		pf_spaces(!pa->zero && !pa->left ? pa->width : 0);
		pf_prefix(pa);
	}
	pc_putchar(nbr % pa->base + (min ? 49 : 48));
}

void		pf_putllong(va_list p, t_params *pa)
{
	long long	nbr;

	pa->width -= 1;
	if (pa->left || pa->precision != -1)
		pa->zero = 0;
	nbr = va_arg(p, long long);
	if ((nbr > 0 && !pa->pos) || nbr == 0)
		pa->width++;
	if (pa->precision != 0 || nbr != 0)
		pf_pllong(nbr, pa);
	else if ((pa->pos == 1 || pa->pos == 2))
	{
		pf_spaces(pa->left ? 0 : pa->width);
		pc_putchar(pa->pos == 1 ? '+' : ' ');
		pa->width--;
	}
	else
		pa->left = 1;
	if (nbr == min_ll())
	{
		pa->precision--;
		pa->width--;
	}
	if (pa->left)
		pf_spaces(pa->width);
}
