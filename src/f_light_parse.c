#include "rt.h"

void	stock_light(t_env *e, char *l1, char *l2)
{
	char *cp;

	cp = ft_str_tolower(l1);
	if (ft_strcmp(cp, "power"))
		return;
	if (ft_strcmp(cp, "color"))
		return;
	if (ft_strcmp(cp, "id"))
		return;

}

void	light_parse(t_env *e, int type, int fd)
{
	char	*line;
	int		res;
	char	*l1;
	char	*l2;

	(void)type;
	while ((res = get_next_line(fd, &line)) > 0)
	{
		if (get_prop(e, line, &l1, &l2))
		{
			free(line);
			return ;
		}
		stock_light(e, l1, l2);
		free(line);
	}
	if (res == -1)
		error(e, READ_ERROR);
}
