/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:48:22 by gperez            #+#    #+#             */
/*   Updated: 2018/10/04 16:50:10 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	a foutre dans un autre fichier utilitaire
*/

static char	*get_name(t_env *e, char *line, int i, int l)
{
	char	*cp;
	int		i_cp;

	while (line[i] != '{' && line[i] != '\0')
	{
		if (is_ignored(line[i]) == 0)
			l++;
		i++;
	}
	i = 0;
	i_cp = 0;
	if (!(cp = malloc(sizeof(char) * l + 1)))
	{
		free(line);
		error(e, MALLOC_ERROR);
	}
	while (line[i] != '{' && line[i] != '\0')
	{
		if (is_ignored(line[i]) == 0)
		{
			cp[i_cp] = line[i];
			i_cp++;
		}
		i++;
	}
	cp[i_cp] = '\0';
	return (cp);
}

static int	link_name(const char *name)
{
	int	i;

	i = 0;
	while (*g_ref[i].name && ft_strcmp(g_ref[i].name, name))
		i++;
	return (g_ref[i].name[0] != '\0' ? i : -1);
}

static void	parse_line(t_env *e, char *line, int fd)
{
	int			i;
	int			l;
	int			t;
	char		*type;
	char		*l_type;

	(void)fd;
	i = 0;
	l = 0;
	type = get_name(e, line, i, l);
	l_type = ft_str_tolower(type);
	free(type);
	if (l_type[0] != '\0')
	{
		if ((t = link_name(l_type)) >= 0)
		{
			ft_putstr("\033[37m");
			ft_putendl(g_ref[t].name);
			g_ref[t].parse(e, t, fd);
			ft_putstr("\033[0m");
		}
		else
			wrong_type(e, l_type, fd, 1);
	}
	else
		free(l_type);
	free(line);
}

void		parse(t_env *e, char *arg)
{
	int		fd;
	int		check;
	char	*line;

	e->s.objs = NULL;
	e->s.lits = NULL;
	e->s.cams = NULL;
	e->s.degs = NULL;
	if ((fd = open(arg, O_RDONLY)) == -1)
		error(e, OPEN_ERROR);
	while ((check = get_next_line(fd, &line)) > 0)
		parse_line(e, line, fd);
	while (e->s.cams != NULL)
	{
		ft_putstr("\033[38;5;31m");
		printf("t:%f %f %f\nr:%f %f %f\nantial: %d\nid: %s\n",
		e->s.cams->t.x, e->s.cams->t.y, e->s.cams->t.z, e->s.cams->dir.x, e->s.cams->dir.y, e->s.cams->dir.z, e->s.cams->antialia, e->s.cams->id, e->s.cams->next);
		e->s.cams = e->s.cams->next;
	}
	while (e->s.lits != NULL)
	{
		ft_putstr("\033[38;5;46m");
		printf("%f %f %f\n%f\n%d\n%s\n%s\n",
		e->s.lits->t.x,e->s.lits->t.y,e->s.lits->t.z,e->s.lits->power,e->s.lits->color,e->s.lits->id,e->s.lits->next);
		e->s.lits = e->s.lits->next;
	}
	while (e->s.objs != NULL)
	{
		ft_putstr("\033[38;5;208m");
		printf("type: %d\nt:%f %f %f\nr:%f %f %f\nv1:%f\ncolor:%d\ndiff:%f\nspec:%f\nid:%s\ndisp:%c\n%s\n%s\n%s\n",
		e->s.objs->type, e->s.objs->t.x, e->s.objs->t.y, e->s.objs->t.z,e->s.objs->r.x, e->s.objs->r.y, e->s.objs->r.z,
		e->s.objs->v1, e->s.objs->color, e->s.objs->diff, e->s.objs->spec, e->s.objs->id, e->s.objs->disp,
		e->s.objs->clips, e->s.objs->deg, e->s.objs->next);
		e->s.objs = e->s.objs->next;
	}
	while (e->s.degs != NULL)
	{
		ft_putstr("\033[38;5;142m");
		printf("t:%f %f %f\ndir:%f %f %f\nc1:%d\nc2:%d\nid:%s\n",
		e->s.degs->t.x, e->s.degs->t.y, e->s.degs->t.z,e->s.degs->dir.x, e->s.degs->dir.y, e->s.degs->dir.z,
		e->s.degs->color1,e->s.degs->color2, e->s.degs->id);
		e->s.degs = e->s.degs->next;
	}
	ft_putstr("\033[0m");
	if (check == -1)
		error(e, READ_ERROR);
	if (close(fd) == -1)
		error(e, CLOSE_ERROR);
}
