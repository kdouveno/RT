/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putpercent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:22:33 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:22:37 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			pf_escape(va_list p, t_params *pa)
{
	(void)p;
	if (!pa->left && !pa->zero)
		pf_spaces(pa->width - 1);
	else if (!pa->left)
	{
		while (pa->width > 1)
		{
			pc_putchar('0');
			pa->width--;
		}
	}
	pc_putchar('%');
	if (pa->left)
		pf_spaces(pa->width - 1);
}
