/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 17:36:22 by kdouveno          #+#    #+#             */
/*   Updated: 2018/10/30 14:23:03 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H
# define BUFF_SIZE	1000
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "libft.h"

int					get_next_line(const int fd, char **line);
char				*ft_strjoin_free(char const *s1, char const *s2);

typedef struct 		s_sline
{
	int				fd;
	char			*content;
	struct s_sline	*next;
}					t_sline;
#endif
