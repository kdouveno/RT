#include "rt.h"

void	link_texture(t_env *e, t_obj *obj, char *file)
{
	printf("%s\n",file);
	if (!file)
		error(e, MALLOC_ERROR);
	if (!(obj->mat.txt = SDL_LoadBMP(file)))
		ft_putendl("\033[38;5;203m"TEXT_ERROR);
	else
		printf("Ca marche \n");
}
