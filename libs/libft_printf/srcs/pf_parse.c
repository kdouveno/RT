/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:21:24 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:21:24 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_parse(char *format, int *i, va_list p)
{
	t_params	pa;

	pa = (t_params){0, 0, 10, 0, 0, 0, 0, 0};
	i[0]++;
	if (!format[*i])
		return (0);
	get_flags(format, i, &pa);
	pa.width = get_width(format, i, p);
	pa.precision = get_precision(format, i, p);
	return (pf_launch(format, i, &pa, p));
}

int		pf_launch(char *fo, int *i, t_params *pa, va_list p)
{
	int j;
	int k;

	j = 0;
	while (j < 81)
	{
		k = 0;
		while (ft_ends()[j].end[k] && ft_ends()[j].end[k] == fo[*i + k])
			k++;
		if (!ft_ends()[j].end[k])
		{
			ft_ends()[j].f(p, pa);
			(*i) += ft_strlen(ft_ends()[j].end);
			if (pa->pos == 404)
				return (1);
			return (0);
		}
		j++;
	}
	return (0);
}

void	get_flags(char *fo, int *i, t_params *pa)
{
	while (ft_strchr("-+0 #", fo[*i]))
	{
		if (fo[*i] == '-')
			pa->left = 1;
		else if (fo[*i] == '+')
			pa->pos = 1;
		else if (fo[*i] == '0')
			pa->zero = 1;
		else if (fo[*i] == '#')
			pa->hash = 1;
		else if (fo[*i] == ' ' && pa->pos != 1)
			pa->pos = 2;
		i[0]++;
	}
}

int		get_width(char *fo, int *i, va_list p)
{
	int j;

	j = 0;
	if (fo[*i] == '*')
		return (va_arg(p, int));
	while (fo[*i + j] >= '0' && fo[*i + j] <= '9')
		j++;
	i[0] += j;
	if (j != 0)
		return (ft_atoi(fo + *i - j));
	return (0);
}

int		get_precision(char *fo, int *i, va_list p)
{
	int j;

	j = 0;
	if (fo[*i] == '.')
	{
		i[0]++;
		if (fo[*i] == '*')
			return (va_arg(p, int));
		while (fo[*i + j] >= '0' && fo[*i + j] <= '9')
			j++;
		i[0] += j;
		return (ft_atoi(fo + *i - j));
	}
	return (-1);
}
