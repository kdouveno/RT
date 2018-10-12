/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:47:42 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/21 17:17:09 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	malloc_split_cells(char **out, const char *s, char c)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	j = -1;
	len = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (len > 0)
				out[j] = ft_strnew(len);
			len = 0;
		}
		else
		{
			len++;
			if (len == 1)
				j++;
		}
		i++;
	}
	if (len > 0)
		out[j] = ft_strnew(len);
}

static void	fill_split_cells(char **out, const char *s, char c)
{
	int i;

	while (*s == c)
		s++;
	i = 0;
	while (*s != c && *s)
	{
		(*out)[i] = *s;
		i++;
		s++;
	}
	if (!*s)
		return ;
	(*out)[i] = '\0';
	fill_split_cells(out + 1, s, c);
}

static void	count_words(char const *s, char c, int *len, int *b)
{
	int i;

	i = 0;
	*len = 0;
	*b = 0;
	while (s[i])
	{
		if (s[i] == c)
			*b = 0;
		else
		{
			if (*b == 0)
				(*len)++;
			*b = 1;
		}
		(i)++;
	}
}

char		**ft_strsplit(char const *s, char c)
{
	int		len;
	int		b;
	char	**out;

	if (s == NULL)
		return (NULL);
	count_words(s, c, &len, &b);
	if (!(out = (char **)malloc(sizeof(void*) * len + 1)))
		return (NULL);
	out[len] = NULL;
	malloc_split_cells(out, s, c);
	fill_split_cells(out, s, c);
	return (out);
}
