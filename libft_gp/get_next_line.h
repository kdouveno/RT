/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:04:53 by gperez            #+#    #+#             */
/*   Updated: 2018/02/13 21:03:02 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# define BUFF_SIZE 1024

# include "libft.h"
# include "limits.h"
# include <fcntl.h>
# include <stdio.h>

int				get_next_line(const int fd, char **line);

typedef struct	s_ret
{
	int		ret;
	int		len_line;
	int		clonefd;
	int		buf_too_small;
}				t_ret;

typedef struct	s_stat
{
	int				fd;
	char			*buf_static;
	struct s_stat	*save;
	struct s_stat	*next;
}				t_stat;
#endif
