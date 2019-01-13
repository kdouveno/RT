/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 09:47:55 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/16 13:03:02 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *str1, const char *str2)
{
	int i;

	i = 0;
	while ((unsigned char)str1[i] && (unsigned char)str2[i]
			&& (unsigned char)str1[i] == (unsigned char)str2[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
