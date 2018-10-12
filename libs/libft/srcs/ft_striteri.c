/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 11:39:49 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/21 17:06:11 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int i;
	int len;

	if (s == NULL || *s == '\0' || f == NULL)
		return ;
	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		f(i, &(s[i]));
		i++;
	}
}
