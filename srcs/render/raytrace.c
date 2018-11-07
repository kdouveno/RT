/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 10:51:19 by kdouveno          #+#    #+#             */
/*   Updated: 2018/11/07 15:39:52 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	calcule l'intersection et renvoi le t_intersec
**	out(b, t) avec:
**	b l'objet traverse
**	t la distance entre la camera et le point d'intersection exprime en vecteur
**		directeur de la droite line (l.v)
*/

t_insecres	intersec(t_env *e, t_line line)
{
	t_obj		*b;
	t_insecres	out;
	double		tmp;
	t_line		l;

	out = (t_insecres){NULL, 0};
	b = e->s.objs;
	while (b)
	{
		l.m = apply(vecpro(b->t, -1), line.m);
		l.m = unrot(l.m, b->dir);
		l.v = unrot(line.v, b->dir);
		if ((tmp = g_ref[b->type].intersec(l, b->v[0])) > 0
		&& (tmp < out.t || !out.obj))
			out = (t_insecres){b, tmp};
		b = b->next;
	}
	return (out);
}

double		diffuse_light(t_vec lnc[3])
{
	double	out;

	out = scalar_product(lnc[0], lnc[1]);
	return (out);
}

double		spec_light(t_vec lnc[3])
{
	double	out;
	t_vec	h;

	h = normalise((t_vec){
		(lnc[0].x + lnc[2].x) / 2,
		(lnc[0].y + lnc[2].y) / 2,
		(lnc[0].z + lnc[2].z) / 2
	});
	out = pow(scalar_product(h, lnc[1]), 100);
	return (out);
}

t_color		lites(t_rendering *r, t_pt pt, t_obj obj)
{
	t_lit		*l;
	t_color		out;
	t_vec		lnc[3];
	int			i;

	out = (t_color) (unsigned)AMASK;
	l = r->e->s.lits;
	while (l)
	{
		if (intersec(r->e, get_line(l->t, pt)).t > 0.999999 && (i = 0) == 0)
		{
			lnc[0] = normalise(get_line(pt, l->t).v);
			lnc[2] = normalise(get_line(pt, r->c->t).v);
			lnc[1] = normalise(g_ref[obj.type].norm(unrot(apply(vecpro(obj.t, -1),
			pt), obj.dir), obj, lnc[2]));
			out.i |= rgbadd(rgbadd(out, rgbpro(rgbmin(l->color, rgbneg(obj.mat.color)),
			l->power * diffuse_light(lnc))), rgbpro(l->color, l->power *
			spec_light(lnc) * obj.mat.spec)).i;
		}
		l = l->next;
	}
	return (out);
}

/*
**	renvoie la couleur du pixel a afficher pour un rayon de droite
*/

t_color		raytrace(t_rendering *r, t_line l)
{
	t_insecres	res;
	t_color		out;

	pthread_mutex_unlock(&r->lock);
	out = (t_color)(unsigned)AMASK;
	res = intersec(r->e, l);
	if (res.obj)
		out.i |= lites(r, get_linept(l, res.t), *res.obj).i;
	return (out);
}
