/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:47:34 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/16 16:15:55 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *out;

	if (!(out = (char*)ft_memalloc(size + 1)))
		return (NULL);
	ft_memset(out, '\0', size + 1);
	return (out);
}
