/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putuni.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:23:05 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:23:06 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_intuni(int c)
{
	if (c < (1 << 8))
		pc_putchar((char)c);
	else if (c < (1 << 11))
	{
		pc_putchar((char)(0xC0 | ((c & (0x1f << 6)) >> 6)));
		pc_putchar((char)(0x80 | (c & 0x3f)));
	}
	else if (c < (1 << 16))
	{
		pc_putchar((char)(0xe0 | ((c & (0x0f << 12)) >> 12)));
		pc_putchar((char)(0x80 | ((c & (0x3f << 6)) >> 6)));
		pc_putchar((char)(0x80 | (c & 0x3f)));
	}
	else if (c < (1 << 21))
	{
		pc_putchar((char)(0xF0 | ((c >> 18) & 0xF7)));
		pc_putchar((char)(0x80 | ((c >> 12) & 0xBF)));
		pc_putchar((char)(0x80 | ((c >> 6) & 0xBF)));
		pc_putchar((char)(0x80 | (c & 0xBF)));
	}
}

int		ft_miw(int c)
{
	if (c < (1 << 8))
		return (1);
	else if (c < (1 << 11))
		return (2);
	else if (c < (1 << 16))
		return (3);
	else if (c < (1 << 21))
		return (4);
	return (0);
}

void	pf_putuni(va_list p, t_params *pa)
{
	int *str;
	int pre;
	int i;
	int j;

	i = 0;
	if (!(str = va_arg(p, int*)))
		return (pf_pstr("(null)", pa));
	pre = pa->precision;
	while (str[i] && (pa->precision == -1 || (pre = pre - ft_miw(str[i])) >= 0))
		pa->width -= ft_miw(str[i++]);
	if (!pa->left)
		pf_spaces(pa->width);
	j = 0;
	while (j < i)
	{
		if (pf_cant_put_that_bloody_unicode_caractere(str[j]))
		{
			pa->pos = 404;
			break ;
		}
		ft_intuni(str[j++]);
	}
	if (pa->left)
		pf_spaces(pa->width);
}
