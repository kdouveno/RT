/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhuang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:17:56 by anhuang           #+#    #+#             */
/*   Updated: 2018/02/23 11:56:14 by kdouveno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <locale.h>
# include <wchar.h>
# include "libft.h"
# define BS 128

typedef struct	s_params
{
	int				width;
	int				precision;
	unsigned short	base;
	unsigned short	left;
	unsigned short	neg;
	unsigned short	pos;
	unsigned short	zero;
	unsigned short	hash;
}				t_params;

typedef struct	s_ends
{
	char *end;
	void (*f)(va_list p, t_params* pa);
}				t_ends;

int				ft_printf(char *format, ...);

void			pc_putchar(char c);
int				pc_print(int pos);
void			pc_putstr(char *str);
void			pc_fill(t_params *pa);
int				pc_core(char c, int param, int dpos);

t_ends			*ft_ends(void);
int				pf_parse(char *f, int *i, va_list p);
void			get_flags(char *fo, int *i, t_params *pa);
int				get_width(char *fo, int *i, va_list p);
void			get_end(char *fo, int *i);
int				get_precision(char *fo, int *i, va_list p);
int				pf_launch(char *fo, int *i, t_params *pa, va_list p);
short			is_flag(char c);
short			is_length(char c);

void			pf_putstring(va_list p, t_params *pa);

void			pf_putstr(va_list p, t_params *pa);
void			pf_pstr(char *c, t_params *pa);

int				pf_cant_put_that_bloody_unicode_caractere(unsigned int c);
void			pf_putuni(va_list p, t_params *pa);
void			ft_intuni(int c);
int				ft_miw(int c);

void			pf_putcuni(va_list p, t_params *pa);

void			pf_putmxchard(va_list p, t_params *pa);
void			pf_putmxshort(va_list p, t_params *pa);
void			pf_putmxint(va_list p, t_params *pa);
void			pf_putmxlong(va_list p, t_params *pa);
void			pf_putmxllong(va_list p, t_params *pa);

void			pf_putchard(va_list p, t_params *pa);
void			pf_putshort(va_list p, t_params *pa);
void			pf_putint(va_list p, t_params *pa);
void			pf_putlong(va_list p, t_params *pa);
void			pf_putllong(va_list p, t_params *pa);

void			pf_putuchard(va_list p, t_params *pa);
void			pf_putushort(va_list p, t_params *pa);
void			pf_putuint(va_list p, t_params *pa);
void			pf_putulong(va_list p, t_params *pa);
void			pf_putullong(va_list p, t_params *pa);

void			pf_putochard(va_list p, t_params *pa);
void			pf_putoshort(va_list p, t_params *pa);
void			pf_putoint(va_list p, t_params *pa);
void			pf_putolong(va_list p, t_params *pa);
void			pf_putollong(va_list p, t_params *pa);

void			pf_putxchard(va_list p, t_params *pa);
void			pf_putxshort(va_list p, t_params *pa);
void			pf_putxint(va_list p, t_params *pa);
void			pf_putxlong(va_list p, t_params *pa);
void			pf_putxllong(va_list p, t_params *pa);

void			pf_putpointer(va_list p, t_params *pa);

void			pf_putmxchard(va_list p, t_params *pa);
void			pf_putmxshort(va_list p, t_params *pa);
void			pf_putmxint(va_list p, t_params *pa);
void			pf_putmxlong(va_list p, t_params *pa);
void			pf_putmxllong(va_list p, t_params *pa);

void			pf_putc(va_list p, t_params *pa);

void			pf_escape(va_list p, t_params *pa);

void			pf_prefix(t_params *pa);
void			pf_spaces(int width);

long long		min_ll();
long			min_l();
int				min_i();
short			min_s();
char			min_c();
size_t			min_st();
intmax_t		min_im();

#endif
