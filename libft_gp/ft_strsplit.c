/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 20:05:21 by gperez            #+#    #+#             */
/*   Updated: 2017/11/23 15:53:00 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_sub_nb_s(char const *s, char c)
{
	int		cmpt;
	int		nb_s;

	cmpt = 0;
	nb_s = 0;
	while (s[cmpt])
	{
		while (s[cmpt] == c)
			cmpt++;
		if (s[cmpt])
			nb_s++;
		while (s[cmpt] != c && s[cmpt])
			cmpt++;
	}
	return (nb_s);
}

static int		*ft_sub_calc_c(int *tab_t, char const *s, char c)
{
	int		cmpt;
	int		taille;
	int		nb_s;

	cmpt = 0;
	taille = 0;
	nb_s = 0;
	while (s[cmpt])
	{
		while (s[cmpt] == c)
			cmpt++;
		if (s[cmpt])
			nb_s++;
		while (s[cmpt] != c && s[cmpt])
		{
			taille++;
			cmpt++;
		}
		while (s[cmpt] == c)
			cmpt++;
		tab_t[nb_s - 1] = taille;
		taille = 0;
	}
	return (tab_t);
}

static char		**ft_subs_split(char **tab_s, char const *s, char c)
{
	int		cmpt;
	int		cmpt_m;
	int		cmpt_l;

	cmpt = 0;
	cmpt_m = 0;
	cmpt_l = 0;
	while (s[cmpt])
	{
		while (s[cmpt] == c)
			cmpt++;
		while (s[cmpt] != c && s[cmpt])
		{
			tab_s[cmpt_m][cmpt_l] = s[cmpt];
			cmpt_l++;
			cmpt++;
		}
		tab_s[cmpt_m][cmpt_l] = '\0';
		cmpt_m++;
		cmpt_l = 0;
		while (s[cmpt] == c)
			cmpt++;
	}
	tab_s[cmpt_m] = NULL;
	return (tab_s);
}

static char		**ft_sub_split(char **tab_s, char const *s, char c, int nb_s)
{
	int		*tab_t;
	int		i;

	i = 0;
	if (!(tab_t = (int *)malloc(sizeof(int) * nb_s)))
		return (NULL);
	tab_t = ft_sub_calc_c(tab_t, s, c);
	while (i < nb_s)
	{
		if (!(tab_s[i] = (char *)malloc(sizeof(char) * (tab_t[i] + 1))))
			return (NULL);
		i++;
	}
	if (!(tab_s[i] = (char *)malloc(sizeof(char) * 1)))
		return (NULL);
	return (ft_subs_split(tab_s, s, c));
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab_s;
	int		nb_s;

	if (s)
	{
		nb_s = ft_sub_nb_s(s, c);
		if (nb_s == 0)
		{
			if (!(tab_s = (char **)malloc(sizeof(char*) * 2)))
				return (NULL);
			if (!(tab_s[0] = (char *)malloc(sizeof(char) * 1)))
				return (NULL);
			tab_s[0] = NULL;
			return (tab_s);
		}
		if (!(tab_s = (char **)malloc(sizeof(char*) * nb_s + 1)))
			return (NULL);
		return (ft_sub_split(tab_s, s, c, nb_s));
	}
	return (NULL);
}
