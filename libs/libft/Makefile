LIB? = d
ifndef LIB?
NAME = rtone
else
NAME = $(notdir $(shell pwd))
endif

FLAGS = -Wall -Werror -Wextra


FW = OpenGl\
	 AppKit

CC = gcc

FWL = $(addprefix -framework ,$(FW))
rwildcard = $(if $1,$(if $(wildcard $1/*),$(foreach p,$(wildcard $1/*),\
	$(call rwildcard,$(filter-out $(subst *,%,$2),$p),$2)\
	$(filter $(subst *,%,$2),$p))))
SRCS = $(call rwildcard,srcs,*.c)
INCS = -I./includes $(addprefix -I, $(call rwildcard,libs,*/includes))
OBJS = $(patsubst srcs/%.c,objs/%.o,$(SRCS))
MKES = $(dir $(wildcard libs/*/Makefile))
ARCH = $(addsuffix .a, $(patsubst %/,%,$(MKES)))
ARCF = $(filter-out $(ARCH), $(wildcard libs/*.a))
TARGET = $(if $(LIB?),../)$(NAME)$(if $(LIB?),.a)
BLUE = \033[38;5;117m
RED = \033[38;5;203m
GREEN = \033[38;5;120m
VIOLET = \033[38;5;135m
WHITE = \033[37m

all: $(TARGET)

$(TARGET): $(OBJS) $(ARCH)
ifdef LIB?
	@ar rc $@ $^
	@ranlib $@
	@printf "$(VIOLET)%15s : $(GREEN)succesfuly made! %10.0d\n" $@ 0
endif
ifndef LIB?
	@$(CC) $(FLAGS) $(FWL) $(ARCF) $^ -o $@
	@printf "$(VIOLET)%15s : $(GREEN)succesfuly made!%20.0d\n" $(TARGET) 0
endif

%.a: %/
	@make -C $^

objs/%.o: srcs/%.c
	@[ -d $(dir $@) ] || (mkdir $(dir $@) && printf "$(VIOLET)%15s : $(WHITE)mkdir: %s\n" $(NAME) $(dir $@))
	@printf "$(VIOLET)%15s : $(BLUE)%-20s$(WHITE) ...\r" $(NAME) $(<F)
	@gcc -c -o $@ $(FLAGS) $(INCS) $^
	@printf "$(VIOLET)%15s : $(BLUE)%-20s$(GREEN) done$(WHITE)\n" $(NAME) $(<F)

debug:
	@printf "%s\n" $(NAME)

clean:
	@$(foreach p,$(MKES),make -C $(p) clean;)
	@[ -d "./objs" ] && rm -rf objs && printf "$(VIOLET)%15s : $(RED)objs destroyed\n" $(NAME) || printf "$(VIOLET)%15s : $(BLUE)object files not found\n" $(NAME)

tclean:
	@$(foreach p,$(MKES),make -C $(p) tclean;)
	@[ -f $(TARGET) ] && rm -rf $(TARGET) && printf "$(VIOLET)%15s : $(RED)%s destroyed\n" $(NAME) $(TARGET) || printf "$(VIOLET)%15s : $(BLUE)Target file %s not found\n" $(NAME) $(TARGET)

fclean: clean tclean
	@printf "\n"

re: clean all

.PHONY: re tclean clean debug all
