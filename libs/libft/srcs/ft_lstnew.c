/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 16:39:32 by kdouveno          #+#    #+#             */
/*   Updated: 2017/11/21 17:40:18 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*out;
	void	*cont;

	if (!content)
		content_size = 0;
	out = (t_list*)malloc(sizeof(t_list));
	if (!out)
		return (NULL);
	cont = ft_memalloc(content_size);
	if (!cont)
		return (NULL);
	if (!content)
		out->content = NULL;
	else
		out->content = ft_memcpy(cont, content, content_size);
	out->content_size = content_size;
	out->next = NULL;
	return (out);
}
