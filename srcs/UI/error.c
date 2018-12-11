/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:32:23 by schaaban          #+#    #+#             */
/*   Updated: 2018/11/06 16:43:54 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtui.h"

void				error_handler(t_rt *rt, int error_code)
{
	if (error_code == ERR_MALLOC)
		ft_putendl_fd("error: memory allocation failed", 2);
	rt_exit(rt);
}
