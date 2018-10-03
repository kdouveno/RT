/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 17:00:54 by gperez            #+#    #+#             */
/*   Updated: 2017/11/24 00:56:45 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_subs_strtrim(char const *s, int cmpt, int lim, int deb)
{
	char	*ret;

	if (!(ret = (char *)malloc(sizeof(char) * (lim - deb) + 1)))
		return (NULL);
	cmpt = 0;
	while (deb < lim)
	{
		ret[cmpt] = s[deb];
		cmpt++;
		deb++;
	}
	ret[cmpt] = '\0';
	return (ret);
}

static char	*ft_sub_strtrim(char const *s, int cmpt, int lim, int deb)
{
	while (s[cmpt] == ' ' || s[cmpt] == '\n' || s[cmpt] == '\t')
		cmpt++;
	deb = cmpt;
	if (s[cmpt] == '\0')
		lim = deb;
	while (s[cmpt])
	{
		lim = ft_strlen(s);
		while (s[cmpt] != ' ' && s[cmpt] != '\n' && s[cmpt] != '\t' && s[cmpt])
			cmpt++;
		if (s[cmpt] == ' ' || s[cmpt] == '\n' || s[cmpt] == '\t')
		{
			lim = cmpt;
			while (s[cmpt] == ' ' || s[cmpt] == '\n' || s[cmpt] == '\t')
				cmpt++;
		}
	}
	return (ft_subs_strtrim(s, cmpt, lim, deb));
}

char		*ft_strtrim(char const *s)
{
	int		cmpt;
	int		lim;
	int		deb;

	if (s)
	{
		cmpt = 0;
		lim = 0;
		deb = 0;
		return (ft_sub_strtrim(s, cmpt, lim, deb));
	}
	return (NULL);
}
