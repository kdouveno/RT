#include "rt.h"
/*
int		check_pt(t_lit *lit, char* l1, char *l2)
{
	if (!(ft_strcmp(l1, "tx")))
	{
		lit->t.x = ft_atod(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "ty")))
	{
		lit->t.y = ft_atod(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "tz")))
	{
		lit->t.z = ft_atod(l2);
		return (0);
	}
	return (1);
}

int		check_arg(t_lit *lit, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "power")))
	{
		lit->power = ft_atod(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "color")))
	{
		lit->color = (t_color)ft_atoi(l2);
		return (0);
	}
	if (!(ft_strcmp(l1, "id")))
	{
		lit->id = l2;
		return (0);
	}
	return(1);
}
*/
/*void	check_rot(t_lit *lit, char* l1, char *l2)
{
	if (ft_strcmp(l1, "rx"))
	{
		lit->r.x = ft_atod(l2);
		return;
	}
	if (ft_strcmp(l1, "ry"))
	{
		lit->r.y = ft_atod(l2);
		return;
	}
	if (ft_strcmp(l1, "rz"))
	{
		lit->r.z = ft_atod(l2);
		return;
	}
}

void	stock_light(t_env *e, t_lit *lit, char *l1, char *l2)
{
	char	*cp;
	int		i;

	i = 0;
	cp = ft_str_tolower(l1);
	if (check_pt(lit, cp, l2) == 1)
	{
		while (is_ignored(l1[i]) == 1)
			i++;
		if (l1[i] != '\0')
			wrong_type(e, l1, 0, 0);
	}
	free(cp);
}
*/
void	light_parse(t_env *e, int type, int fd)
{
/*	char	*line;
	int		res;
	char	*l1;
	char	*l2;
	t_lit	*lit;

	(void)type;
	if (!(lit = malloc(sizeof(t_lit))))
		error(e, MALLOC_ERROR);
	*lit = (t_lit){(t_pt){0, 0, 0}, 0, 0 , NULL, NULL};
	while ((res = get_next_line(fd, &line)) > 0)
	{
		if (get_prop(e, line, &l1, &l2))
		{
			free(line);
			return ;
		}
		stock_light(e, lit, l1, l2);
		free(line);
	}
	if (res == -1)
		error(e, READ_ERROR);
	if (e->s.lits != NULL)
	{
		while(e->s.lits != NULL)
			e->s.lits = e->s.lits->next;
	}
	e->s.lits = lit;*/
	(void)e;
	(void)type;
	(void)fd;
}
