/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:20:38 by gperez            #+#    #+#             */
/*   Updated: 2018/11/13 17:57:45 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		error(t_env *e, const char *msg)
{
	ft_putstr("\033[38;5;203m");
	ft_putendl(msg);
	ft_putstr("\033[0m");
	quit(e, NULL);
}

void		quit(t_env *e, const char *msg)
{
	if (msg)
	{
		ft_putstr("\033[38;5;203m");
		ft_putendl(msg);
		ft_putstr("\033[0m");
	}
	free_scene(&(e->s));
	free_prst(e->p);
	exit(0);
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
