/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:21:47 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:21:50 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_pint(int nbr, t_params *pa)
{
	int min;

	if ((min = (nbr == min_i())))
	{
		pa->neg = 1;
		pa->width--;
		pa->precision--;
		pf_pint((nbr - 1) / pa->base, pa);
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
		pf_pint(nbr / (int)pa->base, pa);
	else if (!min)
	{
		pf_spaces(!pa->zero && !pa->left ? pa->width : 0);
		pf_prefix(pa);
	}
	pc_putchar(nbr % pa->base + (min ? 49 : 48));
}

void	pf_putint(va_list p, t_params *pa)
{
	int nbr;

	pa->width -= 1;
	if (pa->left || pa->precision != -1)
		pa->zero = 0;
	nbr = va_arg(p, int);
	if (nbr >= 0 && !pa->pos)
		pa->width++;
	if (pa->precision != 0 || nbr != 0)
		pf_pint(nbr, pa);
	else if ((pa->pos == 1 || pa->pos == 2))
	{
		pf_spaces(pa->left ? 0 : pa->width);
		pc_putchar(pa->pos == 1 ? '+' : ' ');
		pa->width--;
	}
	else
		pa->left = 1;
	if (nbr == min_i())
		pa->width--;
	if (pa->left)
		pf_spaces(pa->width);
}

void	pf_prefix(t_params *pa)
{
	if (pa->neg)
		pc_putchar('-');
	else if (pa->pos == 1)
		pc_putchar('+');
	else if (pa->pos == 2)
		pc_putchar(' ');
	else if (pa->hash && pa->base == 8)
		pc_putchar('0');
	else if ((pa->hash && pa->base == 16) || pa->pos == 20)
	{
		pc_putchar('0');
		pc_putchar(pa->pos == 80 ? 'X' : 'x');
	}
}

void	pf_spaces(int n)
{
	while (n > 0)
	{
		pc_putchar(' ');
		n--;
	}
}
