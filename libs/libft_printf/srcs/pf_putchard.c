/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putchard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:21:34 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:21:39 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_pchard(char nbr, t_params *pa)
{
	char min;

	if ((min = (nbr == min_c())))
	{
		pa->neg = 1;
		pf_pchard((nbr - 1) / pa->base, pa);
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
		pf_pchard(nbr / (char)pa->base, pa);
	else if (!min)
	{
		pf_spaces(!pa->zero && !pa->left ? pa->width : 0);
		pf_prefix(pa);
	}
	pc_putchar(nbr % pa->base + (min ? 49 : 48));
}

void	pf_putchard(va_list p, t_params *pa)
{
	char nbr;

	pa->width -= 1;
	if (pa->left || pa->precision != -1)
		pa->zero = 0;
	nbr = (char)va_arg(p, int);
	if ((nbr > 0 && !pa->pos) || nbr == 0)
		pa->width++;
	if (pa->precision != 0 || nbr != 0)
		pf_pchard(nbr, pa);
	else if ((pa->pos == 1 || pa->pos == 2))
	{
		pf_spaces(pa->left ? 0 : pa->width);
		pc_putchar(pa->pos == 1 ? '+' : ' ');
		pa->width--;
	}
	else
		pa->left = 1;
	if (nbr == min_c())
	{
		pa->precision--;
		pa->width--;
	}
	if (pa->left)
		pf_spaces(pa->width);
}
