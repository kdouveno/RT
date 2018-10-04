/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:49:52 by gperez            #+#    #+#             */
/*   Updated: 2018/10/04 16:56:23 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cam_parse(t_env *e, int type, int fd)
{
	char	*line;
	int		res;
	char	*l1;
	char	*l2;
//	t_cam

	(void)type;
	while ((res = get_next_line(fd, &line)) > 0)
	{
		if (get_prop(e, line, &l1, &l2))
			return ;
		free(line);
	}
}
