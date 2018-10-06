# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gperez <gperez@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/12 11:56:47 by gperez            #+#    #+#              #
#    Updated: 2018/10/04 16:57:57 by gperez           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

FLAG = -Wall -Werror -Wextra

LIBS = libft/libft.a

MLXI = /usr/local/include
MLXL = /usr/local/lib

GL = -framework OpenGL
APP = -framework AppKit

SRC_DIR =	src/
SRC_LIST =	main.c \
			f_parser.c \
			f_get_prop.c \
			f_cam_parse.c \
			f_wrong_type.c \
			f_light_parse.c \
			is_name_char.c \
			is_ignored.c \

INCDIR = -Ilibft/includes -Iincludes -Ilibft_gp

OBJS = $(SRC_LIST:.c=.o)

all : $(NAME)

NC = \033[0m
BOLD =\033[1m
DIM =\033[2m
ITALIC =\033[3m
UNDER =\033[4m
BLINK =\033[5m

RS_BO = \033[21m
RS_D = \033[22m
RS_I = \033[23m
RS_U =\033[24m
RS_BL = \033[25m

WHITE = \033[37m
BLUE = \033[38;5;37m
CYAN = \033[38;5;117m
GREEN = \033[38;5;120m
MAGENTA = \033[38;5;135m
RED = \033[38;5;203m


$(NAME) : $(OBJS)
	@make -C libft
	@gcc $(FLAG) -I $(MLXI) -L $(MLXL) -lmlx libft/libft.a $(GL) $(APP) $^ -o $(NAME)
	@printf "$(BOLD)$(BLINK)$(MAGENTA)%20s : $(RS_BL)$(RS_BO)$(GREEN)succesfuly made!$(NC)\n" $(NAME)

pain : $(OBJS) libft_gp/*.c
	@make -C libft_gp
	@gcc $(OBJS) $(INCDIR) ../minilibx/libmlx_Linux.a -lX11 -lXext -lbsd -lm libft_gp/libft.a -o $@
	@printf "$(BOLD)$(MAGENTA)%20s : $(RS_BO)$(GREEN)succesfuly made!$(NC)\n" $(NAME)

%.o : $(SRC_DIR)%.c
	@printf "$(BOLD)$(MAGENTA)%20s : $(RS_BO)$(CYAN)%-20s$(WHITE) ...$(NC)" $(NAME) $(<F)
	@gcc $(FLAG) $(INCDIR) -o $@ -c $<
	@printf "\r$(MAGENTA)%20s : $(CYAN)%-20s$(GREEN) done\n$(WHITE)" $(NAME) $(<F)
clean :
	@make -C libft fclean
	@make -C libft_gp fclean
	@printf "$(BOLD)$(MAGENTA)%20s : $(RED)clean$(NC)\n" libft
	@/bin/rm -rf *.o
	@printf "$(BOLD)$(MAGENTA)%20s : $(RED)deleted$(NC)\n" *.o

fclean : clean
	@/bin/rm -rf $(NAME)
	@printf "$(BOLD)$(MAGENTA)%20s : $(RED)deleted$(NC)\n" $(NAME)
	@/bin/rm -rf $(LIBS)
	@printf "$(BOLD)$(MAGENTA)%20s : $(RED)deleted$(NC)\n" $(LIBS)
	@/bin/rm -rf pain


re : fclean all
