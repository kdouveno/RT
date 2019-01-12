/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_refraction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <kdouveno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 12:57:00 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/12 14:24:07 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			n_rec_clip(t_obj *wanted, int *n_rec, int n, t_obj *cur)
{
	t_objlist	*c;

	c = cur->clipping;
	if (!c || (c->obj == wanted && n < n_rec[0]))
		n_rec[0] = n;
	while (c)
	{
		n_rec_clip(wanted, n_rec, n + 1, c->obj);
		c = c->next;
	}
}

inline static void	compute_n(t_ri *ri, t_reslist res)
{
	int		n_rec;
	t_vec	inout;
	int		i;
	t_ri	*r;

	n_rec = 0;
	n_rec_clip(ri->o, &n_rec, 0, ri->co);
	inout = (n_rec % 2) ? res.tn : rev_3d(res.tn);
	ri->c = (scalar_product(inout, res.cam) > 0) ? '+' : '-';
	i = 0;
	r = ri;
	while (r && r->c != '.')
	{
		if (r->c == '+' && i++)
			ri->n += r->o->mat.n;
		else if (r->c == '-' && i--)
			ri->n -= r->o->mat.n;
		r = r->next;
	}
	if (i <= 0)
		ri->c = '.';
	ri->n =  ri->n / (double)i;
}

t_color				refraction(t_rendering *r, t_reslist res, int bounce, t_ri *ri)
{
	double	n;
	double  c[2];
	t_vec	t;
	t_ri	out;

	out = (t_ri){ri, res.o, res.co, 0, '+'};
	compute_n(&out, res);
	res.n = res.pert.x == 0 && res.pert.y == 0 && res.pert.z == 0 ? res.n : rot(res.pert, get_rot(res.n, 0));
	n = (ri->o ? ri->n : 1) / out.o->mat.n;
	c[0] = scalar_product(res.cam, res.n);
	c[1] = sqrt(1 - sq(n) * (1 - sq(c[0])));
	t = apply(rev_3d(vecpro(res.cam, n)), vecpro(res.n, n * c[0] - c[1]));
	return (raytrace(r, (t_line){res.pt, t}, bounce, out));
}