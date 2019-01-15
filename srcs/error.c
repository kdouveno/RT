/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:20:38 by gperez            #+#    #+#             */
/*   Updated: 2019/01/15 16:45:18 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		error(t_env *e, const char *msg)
{
	(void)e;
	ft_putstr("\033[38;5;203m");
	ft_putendl(msg);
	ft_putstr("\033[0m");
	rt_exit(e);
}

void		error_prst(t_prst *p, char *msg)
{
	ft_putstr("\033[38;5;203m");
	ft_putendl(msg);
	ft_putstr("\033[0m");
	if (p->next)
		error_prst(p->next, msg);
	free_scene(&(p->s));
	ft_memdel((void**)&p);
}
