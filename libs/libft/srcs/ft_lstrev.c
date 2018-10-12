/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:37:31 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/21 12:38:00 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstrev(t_list *lst)
{
	t_list	*out;

	out = NULL;
	while (lst)
	{
		ft_lstadd(&out, lst);
		lst = lst->next;
	}
	return (out);
}
