/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ends.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdouveno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:21:19 by kdouveno          #+#    #+#             */
/*   Updated: 2018/02/21 15:21:20 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	end_four(t_ends *out, int *i)
{
	out[(*i)++] = (t_ends){"zp", &pf_putpointer};
	out[(*i)++] = (t_ends){"jp", &pf_putpointer};
	out[(*i)++] = (t_ends){"d", &pf_putint};
	out[(*i)++] = (t_ends){"D", &pf_putlong};
	out[(*i)++] = (t_ends){"i", &pf_putint};
	out[(*i)++] = (t_ends){"o", &pf_putoint};
	out[(*i)++] = (t_ends){"O", &pf_putolong};
	out[(*i)++] = (t_ends){"x", &pf_putxint};
	out[(*i)++] = (t_ends){"X", &pf_putmxint};
	out[(*i)++] = (t_ends){"p", &pf_putpointer};
	out[(*i)++] = (t_ends){"S", &pf_putuni};
	out[(*i)++] = (t_ends){"s", &pf_putstr};
	out[(*i)++] = (t_ends){"C", &pf_putcuni};
	out[(*i)++] = (t_ends){"c", &pf_putc};
	out[(*i)++] = (t_ends){"u", &pf_putuint};
	out[(*i)++] = (t_ends){"U", &pf_putulong};
	out[(*i)++] = (t_ends){"%", &pf_escape};
}

static void	end_three(t_ends *out, int *i)
{
	out[(*i)++] = (t_ends){"jO", &pf_putollong};
	out[(*i)++] = (t_ends){"zo", &pf_putollong};
	out[(*i)++] = (t_ends){"zO", &pf_putollong};
	out[(*i)++] = (t_ends){"lu", &pf_putulong};
	out[(*i)++] = (t_ends){"hu", &pf_putushort};
	out[(*i)++] = (t_ends){"ju", &pf_putullong};
	out[(*i)++] = (t_ends){"zu", &pf_putullong};
	out[(*i)++] = (t_ends){"ju", &pf_putullong};
	out[(*i)++] = (t_ends){"jU", &pf_putullong};
	out[(*i)++] = (t_ends){"zU", &pf_putullong};
	out[(*i)++] = (t_ends){"lU", &pf_putullong};
	out[(*i)++] = (t_ends){"hU", &pf_putullong};
	out[(*i)++] = (t_ends){"hx", &pf_putxshort};
	out[(*i)++] = (t_ends){"lx", &pf_putxlong};
	out[(*i)++] = (t_ends){"jx", &pf_putxllong};
	out[(*i)++] = (t_ends){"zx", &pf_putxllong};
	out[(*i)++] = (t_ends){"hX", &pf_putmxshort};
	out[(*i)++] = (t_ends){"lX", &pf_putmxlong};
	out[(*i)++] = (t_ends){"jX", &pf_putmxllong};
	out[(*i)++] = (t_ends){"lO", &pf_putollong};
	out[(*i)++] = (t_ends){"hO", &pf_putoint};
	out[(*i)++] = (t_ends){"zX", &pf_putmxllong};
	out[(*i)++] = (t_ends){"hp", &pf_putpointer};
	out[(*i)++] = (t_ends){"lp", &pf_putpointer};
	end_four(out, i);
}

static void	end_two(t_ends *out, int *i)
{
	out[(*i)++] = (t_ends){"hhS", &pf_putuni};
	out[(*i)++] = (t_ends){"hhC", &pf_putcuni};
	out[(*i)++] = (t_ends){"hhO", &pf_putoshort};
	out[(*i)++] = (t_ends){"hhp", &pf_putpointer};
	out[(*i)++] = (t_ends){"llp", &pf_putpointer};
	out[(*i)++] = (t_ends){"hhU", &pf_putushort};
	out[(*i)++] = (t_ends){"hd", &pf_putshort};
	out[(*i)++] = (t_ends){"lD", &pf_putllong};
	out[(*i)++] = (t_ends){"hD", &pf_putint};
	out[(*i)++] = (t_ends){"hO", &pf_putoint};
	out[(*i)++] = (t_ends){"ld", &pf_putlong};
	out[(*i)++] = (t_ends){"zd", &pf_putllong};
	out[(*i)++] = (t_ends){"jd", &pf_putllong};
	out[(*i)++] = (t_ends){"jD", &pf_putllong};
	out[(*i)++] = (t_ends){"zD", &pf_putllong};
	out[(*i)++] = (t_ends){"hi", &pf_putshort};
	out[(*i)++] = (t_ends){"li", &pf_putlong};
	out[(*i)++] = (t_ends){"zi", &pf_putllong};
	out[(*i)++] = (t_ends){"ji", &pf_putllong};
	out[(*i)++] = (t_ends){"ls", &pf_putuni};
	out[(*i)++] = (t_ends){"lc", &pf_putcuni};
	out[(*i)++] = (t_ends){"ho", &pf_putoshort};
	out[(*i)++] = (t_ends){"lo", &pf_putollong};
	out[(*i)++] = (t_ends){"jo", &pf_putollong};
	end_three(out, i);
}

t_ends		*ft_ends(void)
{
	static t_ends	out[81];
	int				i;

	i = 0;
	if (out[0].end == NULL)
	{
		out[i++] = (t_ends){"lld", &pf_putllong};
		out[i++] = (t_ends){"lli", &pf_putllong};
		out[i++] = (t_ends){"hhd", &pf_putchard};
		out[i++] = (t_ends){"hhi", &pf_putchard};
		out[i++] = (t_ends){"hhu", &pf_putuchard};
		out[i++] = (t_ends){"llu", &pf_putullong};
		out[i++] = (t_ends){"hhx", &pf_putxchard};
		out[i++] = (t_ends){"llx", &pf_putxllong};
		out[i++] = (t_ends){"hhX", &pf_putmxchard};
		out[i++] = (t_ends){"llX", &pf_putmxllong};
		out[i++] = (t_ends){"hho", &pf_putochard};
		out[i++] = (t_ends){"llo", &pf_putollong};
		out[i++] = (t_ends){"llO", &pf_putoshort};
		out[i++] = (t_ends){"llD", &pf_putllong};
		out[i++] = (t_ends){"hhD", &pf_putint};
		out[i++] = (t_ends){"llU", &pf_putullong};
		end_two(out, &i);
	}
	return (out);
}
