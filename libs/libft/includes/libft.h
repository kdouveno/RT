/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schaaban <schaaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 13:13:48 by kdouveno          #+#    #+#             */
/*   Updated: 2019/01/19 15:03:11 by schaaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "gnl.h"
# define SP_C(c) (c == ' ' || c == '\n' || c == '\t')
# define ABS(n) (n < 0 ? -n : n)

int				ft_isupper(int c);
int				ft_islower(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isalnum(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
size_t			ft_strlen(const char *str);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *src, size_t n);
char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *str, int c);
int				ft_strcmp(const char *str1, const char *str2);
int				ft_strncmp(const char *str1, const char *str2, size_t n);
char			*ft_strstr(const char *big, const char *little);
char			*ft_strnstr(const char *big, const char *little, size_t n);
char			*ft_str_tolower(char *s);
char			*ft_str_toupper(char *s);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_bzero(void *s, size_t n);
int				ft_atoi(const char *str);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
void			ft_putchar_fd(char c, int fd);
void			ft_putchar(char c);
void			ft_putstr(const char *str);
void			ft_putstr_fd(const char *str, int fd);
void			ft_putendl(const char *c);
void			ft_putendl_fd(const char *c, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putnbr(int n);
char			*ft_itoa(int n);
char			**ft_strsplit(char const *s, char c);
void			ft_free_tab(char **tab);
char			*ft_strdup(const char *src);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
double			ft_atod(const char *str);
int				ft_extoi(const char *str);

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

t_list			*ft_lstnew(void const	*content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *to_add);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstrev(t_list *lst);
int				ft_sqrt(int nb);

#endif
