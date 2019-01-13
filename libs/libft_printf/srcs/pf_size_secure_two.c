/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_size_secure_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:23:53 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:23:55 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		min_st(void)
{
	static size_t a;

	if (!a)
		a = ((size_t)1 << (sizeof(size_t) * 8 - 1));
	return (a);
}

intmax_t	min_im(void)
{
	static intmax_t a;

	if (!a)
		a = ((intmax_t)1 << (sizeof(intmax_t) * 8 - 1));
	return (a);
}
