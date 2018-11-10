/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 14:36:38 by kdouveno          #+#    #+#             */
/*   Updated: 2018/11/09 18:53:44 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_polyres	solve_polynome(double a, double b, double c)
{
	t_polyres	out;
	double		delta;

	out.type = NORES;
	if (a != 0)
	{
		a *= 2;
		delta = b * b - 2 * a * c;
		if (delta > 0)
		{
			delta = sqrt(delta);
			out.type = TWORES;
			out.a = (-b - delta) / a;
			out.b = (-b + delta) / a;
		}
		else if (!delta)
		{
			out.type = ONERES;
			out.a = -b / a;
		}
	}
	return (out);
}

t_vec	get_vector(t_pt a, t_pt b)
{
	return ((t_vec){b.x - a.x, b.y - a.y, b.z - a.z});
}

t_line	get_line(t_pt a, t_pt b)
{
	return ((t_line){a, get_vector(a, b)});
}

t_pt	get_linept(t_line d, double t)
{
	t_pt out;

	out = (t_pt){d.v.x * t + d.m.x, d.v.y * t + d.m.y, d.v.z * t + d.m.z};
	return (out);
}

double	dist(t_pt a, t_pt b)
{
	return (sqrt(sq(a.x - b.x) + sq(a.y - b.y) + sq(a.z - b.z)));
}

void	add_res(t_env *e, t_reslist **cur, t_reslist t)
{
	t_reslist	*last;
	t_reslist	*tmp;

	if (t.t < 0)
		return ;
	tmp = *cur;
	last = NULL;
	while (tmp && t.t > tmp->t)
	{
		last = tmp;
		tmp = tmp->next;
	}
	t.next = tmp;
	if (!(tmp = (t_reslist*)malloc(sizeof(t_reslist))))
		error(e, MALLOC_ERROR);
	*tmp = t;
	last ? (last->next = tmp) : (*cur = tmp);
}

void	free_res(t_reslist *list)
{
	t_reslist	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}
