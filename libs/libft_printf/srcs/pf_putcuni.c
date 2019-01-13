/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putcuni.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:21:43 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:21:44 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_cant_put_that_bloody_unicode_caractere(unsigned int c)
{
	return ((MB_CUR_MAX == 1 && c > 255) || c > 0xE01EF
	|| (c >= 0xD800 && c <= 0xDB7F) || (c >= 0xDC00 && c <= 0xDFFF));
}

void	pf_putcuni(va_list p, t_params *pa)
{
	int c;

	c = va_arg(p, int);
	pa->width -= pf_cant_put_that_bloody_unicode_caractere(c) ? 0 : ft_miw(c);
	if (!pa->left)
		pf_spaces(pa->width);
	if (!pf_cant_put_that_bloody_unicode_caractere(c))
		ft_intuni(c);
	else
		pa->pos = 404;
	if (pa->left)
		pf_spaces(pa->width);
}
