# include "rt.h"

int		check_file_mat(const char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 4)
	{
		if (ft_strcmp(&(str[len - 4]), ".mat"))
			return (0);
		else
			return (1);
	}
	return (1);
}

void	check_last(const char *str, int *p_c, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			*p_c = i;
		i++;
	}
}

char	*file_name(char *str)
{
	int		len;
	char	*out;
	char	*name;
	int		i;
	int		last;

	check_last(str, &last, '/');
	name = str;
	len = ft_strlen(name);
	if (len > 4)
	{
		if(!(out = malloc(sizeof(char) * len - last - 4 + 1)))
			return (NULL);
		i = 0;
		while (last + 1 < len - 4)
		{
			out[i] = name[last + 1];
			last++;
			i++;
		}
	}
	out[i] = '\0';
	return (out);
}
