/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_size_secure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:23:48 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:23:49 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	min_ll(void)
{
	static long long a;

	if (!a)
		a = ((long long)1 << (sizeof(long long) * 8 - 1));
	return (a);
}

long		min_l(void)
{
	static long a;

	if (!a)
		a = ((long)1 << (sizeof(long) * 8 - 1));
	return (a);
}

int			min_i(void)
{
	static int a;

	if (!a)
		a = ((int)1 << (sizeof(int) * 8 - 1));
	return (a);
}

short		min_s(void)
{
	static short a;

	if (!a)
		a = ((short)(1 << (sizeof(short) * 8 - 1)));
	return (a);
}

char		min_c(void)
{
	static char a;

	if (!a)
		a = ((char)(1 << (sizeof(char) * 8 - 1)));
	return (a);
}
