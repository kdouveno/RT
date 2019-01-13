/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:20:57 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/13 15:31:01 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf(char *format, ...)
{
	va_list	p;
	int		i;
	int		lastpos;

	i = 0;
	lastpos = 0;
	va_start(p, format);
	while (format[i])
	{
		if (format[i] != '%')
		{
			pc_putchar(format[i++]);
		}
		else if (pf_parse(format, &i, p))
		{
			pc_print(lastpos);
			return (-1);
		}
		else
			lastpos = pc_core(0, 3, 0);
	}
	return (pc_print(-1));
}
