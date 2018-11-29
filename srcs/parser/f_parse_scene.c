#include "rt.h"

static int		check_arg(t_env *e, t_scene *s, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "lights")))
	{
		if (!(ft_strcmp(l2, "auto")))
			s->auto_l = 1;
		else
			wrong_type(e, l1, 0, 0);
		return (0);
	}
	return (1);
}

void	stock_scene(t_env *e, char *l1, char *l2, t_scene *s)
{
	char	*cp;
	int		i;

	i = 0;
	cp = ft_str_tolower(l1);
	if (check_arg(e, s, cp, l2) == 1)
	{
		while (is_ignored(l1[i]) == 1)
			i++;
		if (l1[i] != '\0')
			wrong_type(e, l1, 0, 0);
	}
	ft_memdel((void**)&cp);
}
void	parse_scene(t_env *e, int type, int fd, t_scene *s)
{
	char	*line;
	int		res;
	char	*l1;
	char	*l2;

	(void)type;
	while ((res = get_next_line(fd, &line)) > 0 && get_prop(e, line, &l1, &l2) != 1)
	{
		stock_scene(e, l1, l2, s);
		ft_memdel((void**)&l1);
		ft_memdel((void**)&l2);
		ft_memdel((void**)&line);
		if (res == -1)
			error(e, READ_ERROR);
	}
	ft_memdel((void**)&line);
}
