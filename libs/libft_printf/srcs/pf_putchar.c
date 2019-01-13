/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:21:30 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:21:31 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*widen(char *old, int pos)
{
	char *out;

	if (!(out = (char*)malloc((pos / BS + 1) * BS + 1)))
		return (NULL);
	ft_bzero(out, (pos / BS + 1) * BS + 1);
	if (old)
	{
		ft_memcpy(out, old, (pos / BS) * BS);
		free(old);
	}
	return (out);
}

int				pc_core(char c, int param, int dpos)
{
	static int			pos;
	static char			*buffer;
	int					out;

	if (param == 1)
	{
		if (!(pos % BS))
			if (!(buffer = widen(buffer, pos)))
				return (-1);
		buffer[pos] = c;
		pos++;
	}
	else if (!(param & 1))
	{
		out = buffer ? pos : 0;
		if (param == 2)
			out = dpos;
		write(1, buffer ? buffer : "", out);
		free(buffer);
		buffer = NULL;
		pos = 0;
		return (out);
	}
	return (pos);
}

int				pc_print(int pos)
{
	if (pos == -1)
		return (pc_core(0, 0, 0));
	else
		return (pc_core(0, 2, pos));
}

void			pc_putchar(char c)
{
	pc_core(c, 1, 0);
}

void			pc_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		pc_core(str[i], 1, 0);
		i++;
	}
}
