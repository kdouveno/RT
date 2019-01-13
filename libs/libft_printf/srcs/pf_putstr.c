/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:22:50 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:22:50 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_pstr(char *c, t_params *pa)
{
	int	i;

	i = 0;
	while (c[i])
		++i;
	if (!pa->left && pa->precision == -1)
		pf_spaces(pa->width - i);
	else if (!pa->left)
		pf_spaces(pa->width - ((pa->precision < i) ? pa->precision : i));
	i = 0;
	while (c[i] && (pa->precision == -1 || i < pa->precision))
		pc_putchar(c[i++]);
	if (pa->left)
		pf_spaces(pa->width - i);
}

void	pf_putstr(va_list p, t_params *pa)
{
	char	*c;

	c = va_arg(p, char*);
	if (c)
		pf_pstr(c, pa);
	else
		pf_pstr("(null)", pa);
}
