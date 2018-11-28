
#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (s1 != NULL)
		ft_memdel((void**)&s1);
	return (res);
}
