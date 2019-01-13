/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 16:39:28 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/27 09:39:32 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*lst2_start;
	t_list	*lst2;

	if (lst)
	{
		lst2_start = f(lst);
		if (!(lst2_start))
			return (NULL);
		lst2 = lst2_start;
		while (lst->next)
		{
			lst = lst->next;
			if (!(lst))
				return (NULL);
			lst2->next = f(lst);
			lst2 = lst2->next;
		}
	}
	else
		return (NULL);
	return (lst2_start);
}
