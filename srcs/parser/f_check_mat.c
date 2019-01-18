/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_check_mat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperez <gperez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 15:14:11 by gperez            #+#    #+#             */
/*   Updated: 2019/01/18 16:38:51 by gperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	get_coef(double nb)
{
	if (nb < 0.0f)
		return (0.0f);
	else if (nb > 1.0f)
		return (1.0f);
	return (nb);
}

int		check_mat2(t_env *e, t_obj *obj, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "c")) || !(ft_strcmp(l1, "color")))
		parse_color(obj, l2, NULL, 0);
	else if (!ft_strcmp(l1, "reflexion") || !ft_strcmp(l1, "refl"))
		obj->mat.refl = get_coef(ft_atod(l2));
	else if (!ft_strcmp(l1, "txt") || !ft_strcmp(l1, "texture"))
		link_texture(e, obj, ft_strjoin("textures/", l2), 't');
	else if (!ft_strcmp(l1, "txt_bm") || !ft_strcmp(l1, "texture_bump"))
		link_texture(e, obj, ft_strjoin("textures/", l2), 'b');
	else if (!ft_strcmp(l1, "offx"))
		obj->mat.offx = ft_atod(l2) < 0.0f ? -ft_atod(l2) : ft_atod(l2);
	else if (!ft_strcmp(l1, "offy"))
		obj->mat.offy = ft_atod(l2) < 0.0f ? -ft_atod(l2) : ft_atod(l2);
	else if (!ft_strcmp(l1, "b_lvl") || !ft_strcmp(l1, "bump_level"))
		obj->mat.b_lvl = ft_atod(l2);
	else
		return (1);
	return (0);
}

int		check_mat(t_env *e, t_obj *obj, char *l1, char *l2)
{
	if (!(ft_strcmp(l1, "mat")))
	{
		if (check_file_ext(l2, ".mat") && l2[0])
			wrong_type(e, l1, 0, 0);
		else if (l2[0])
			link_mat(e, obj, ft_strjoin("mat/", l2));
	}
	else if (!(ft_strcmp(l1, "spec")))
		obj->mat.spec = ft_atod(l2);
	else if (!(ft_strcmp(l1, "diff")))
		obj->mat.diff = ft_atod(l2);
	else
		return (check_mat2(e, obj, l1, l2));
	return (0);
}
