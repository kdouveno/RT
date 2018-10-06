# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gperez <gperez@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 20:28:46 by gperez            #+#    #+#              #
#    Updated: 2018/10/03 13:25:19 by gperez           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAG = -Wall -Werror -Wextra

TEST = test

SRC =	ft_memset.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memalloc.c \
		ft_memdel.c \
		ft_bzero.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_putendl.c \
		ft_puttab_s.c \
		ft_puttab_int.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_strclr.c \
		ft_strlen.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_swap.c \
		ft_pow.c \
		ft_sqrt.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_strequ.c \
		ft_strnequ.c \
		ft_toupper.c \
		ft_str_toupper.c \
		ft_tolower.c \
		ft_str_tolower.c \
		ft_atoi.c \
		ft_strstr.c \
		ft_strnstr.c \
		ft_strnew.c \
		ft_strdel.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strdup.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strsub.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strsplit.c \
		ft_strcat.c \
		ft_strncat.c \
		ft_strlcat.c \
		ft_strcpy.c \
		ft_strncpy.c \
		ft_itoa.c \
		ft_lstdisplay.c \
		ft_lstmdisplay.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstdel.c \
		ft_lstadd.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_free_tab.c \
		get_next_line.c \
		ft_sq.c \

OBJ = $(SRC:.c=.o)

BLUE = \033[38;5;117m
RED = \033[38;5;203m
GREEN = \033[38;5;120m
MAGENTA = \033[38;5;135m
WHITE = \033[37m

all : $(NAME)

$(NAME) : $(OBJ)
	@ar rcs $(NAME) $^

%.o : %.c
	@printf "$(MAGENTA)%20s : $(BLUE)%-20s$(WHITE) ..." $(NAME) $(<F)
	@gcc $(FLAG) -o $@ -c $<
	@printf "\r$(MAGENTA)%20s : $(BLUE)%-20s$(GREEN) done\n$(WHITE)" $(NAME) $(<F)

test : fclean  $(NAME)
	@gcc $(NAME) main_libft.c -o $(TEST)

clean :
	@/bin/rm -rf *.o

fclean : clean
	@/bin/rm -rf $(NAME) $(TEST)

re : fclean all
