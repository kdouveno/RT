LIB? =
ifndef LIB?
NAME = rt
endif
CC = gcc
FLAGS = -Wall -Werror -Wextra -g
FW =	openGL\
		appKit\
		SDL2
DL = pthread

ifdef LIB?
NAME = $(notdir $(shell pwd))
endif
FWL = $(addprefix -framework ,$(FW))
rwildcard = $(if $1,$(if $(wildcard $1/*),$(foreach p,$(wildcard $1/*),$(call rwildcard,$(filter-out $(subst *,%,$2),$p),$2)$(filter $(subst *,%,$2),$p))))
SRCS = $(call rwildcard,srcs,*.c)
INCS = ./includes /Library/Frameworks/SDL2.framework/Headers $(call rwildcard,libs,*/includes)
MKES = $(dir $(wildcard libs/*/Makefile))
ARCH = $(addsuffix .a, $(patsubst %/,%,$(MKES)))
ARCF = $(filter-out $(ARCH), $(wildcard libs/*.a))
INCSDIR = $(addprefix -I,$(INCS))
INCSFILE = $(foreach d,$(INCS),$(wildcard $d/*.h))
OBJS = $(patsubst srcs/%.c,objs/%.o,$(SRCS))

DLLIST = $(addprefix -l,$(DL))
TARGET = $(if $(LIB?),../)$(NAME)$(if $(LIB?),.a)

BLUE = \033[38;5;117m
RED = \033[38;5;203m
GREEN = \033[38;5;120m
VIOLET = \033[38;5;135m
WHITE = \033[37m

all:
ifneq ($(strip $(MKES)),)
	@make -C $(MKES)
endif
	@make $(TARGET)

$(TARGET): $(OBJS) $(ARCH)
ifdef LIB?
	@ar rc $@ $^
	@ranlib $@
	@printf "$(VIOLET)%15s : $(GREEN)succesfuly made! %10.0d\n" $@ 0
endif
ifndef LIB?
	@$(CC) $(FLAGS) $(FWL) $(DLLIST) $(ARCF) $^ -o $@
	@printf "$(VIOLET)%15s : $(GREEN)succesfuly made!%20.0d\n" $(TARGET) 0
endif

objs/%.o: srcs/%.c $(INCSFILE)
	@[ -d $(dir $@) ] || (mkdir -p $(dir $@) && printf "$(VIOLET)%15s : $(WHITE)mkdir: %s\n" $(NAME) $(dir $@))
	@printf "$(VIOLET)%15s : $(BLUE)%-20s$(WHITE) ...\r" $(NAME) $(<F)
	@$(CC) -c -o $@ $(FLAGS) $(INCSDIR) $<
	@printf "$(VIOLET)%15s : $(BLUE)%-20s$(GREEN) done$(WHITE)\n" $(NAME) $(<F)

debug:
	@printf "%s\n" $(MKES)

clean:
	@$(foreach p,$(MKES),make -C $(p) clean;)
	@[ -d "./objs" ] && rm -rf objs && printf "$(VIOLET)%15s : $(RED)objs destroyed\n" $(NAME) || printf "$(VIOLET)%15s : $(BLUE)object files not found\n" $(NAME)

tclean:
	@$(foreach p,$(MKES),make -C $(p) tclean;)
	@[ -f $(TARGET) ] && rm -rf $(TARGET) && printf "$(VIOLET)%15s : $(RED)%s destroyed\n" $(NAME) $(TARGET) || printf "$(VIOLET)%15s : $(BLUE)Target file %s not found\n" $(NAME) $(TARGET)

fclean: clean tclean
	@printf "\n"

re: fclean all

.PHONY: re fclean tclean clean debug all
