/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 13:46:42 by kdouveno          #+#    #+#             */
/*   Updated: 2018/05/15 17:20:19 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdio.h>

int	main(int argc, char const *argv[])
{
	printf("%.10f\n", ft_atod(argv[1]));
	return (0);
}