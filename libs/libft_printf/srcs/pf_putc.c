/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:21:27 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:21:28 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			pf_putc(va_list p, t_params *pa)
{
	char c;

	c = (char)va_arg(p, int);
	if (!pa->left)
		pf_spaces(pa->width - 1);
	pc_putchar(c);
	if (pa->left)
		pf_spaces(pa->width - 1);
}
