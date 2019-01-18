NAME = rt
CC = gcc
FLAGS = -Wall -Werror -Wextra -O2
FW =	openGL\
		appKit\
		SDL2
DL = pthread

FWL = $(addprefix -framework ,$(FW))
SRCS = \
	srcs/UI/buttons_calls.c \
	srcs/UI/draw.c \
	srcs/UI/event.c \
	srcs/UI/exit.c \
	srcs/UI/gui.c \
	srcs/UI/img_manager.c \
	srcs/UI/init.c \
	srcs/UI/list_button_1.c \
	srcs/UI/list_button_2.c \
	srcs/UI/list_window.c \
	srcs/UI/loop.c \
	srcs/UI/progress_bar.c \
	srcs/UI/struct_aabb.c \
	srcs/UI/update.c \
	srcs/arg.c \
	srcs/atoi_hexa.c \
	srcs/error.c \
	srcs/free_env.c \
	srcs/free_prst.c \
	srcs/geo3d/angles.c \
	srcs/geo3d/colors.c \
	srcs/geo3d/plan.c \
	srcs/geo3d/rotation.c \
	srcs/geo3d/sq.c \
	srcs/geo3d/vector.c \
	srcs/geo3d/vector2.c \
	srcs/init/i_init.c \
	srcs/init/i_link_color_grad.c \
	srcs/init/i_link_color_obj.c \
	srcs/init/i_link_obj.c \
	srcs/init/i_nit_locs.c \
	srcs/init/i_nit_trans.c \
	srcs/main.c \
	srcs/parser/f_check.c \
	srcs/parser/f_check_ext.c \
	srcs/parser/f_check_mat.c \
	srcs/parser/f_creat_clips.c \
	srcs/parser/f_get_prop.c \
	srcs/parser/f_is_ignored.c \
	srcs/parser/f_is_name_char.c \
	srcs/parser/f_is_vec_null.c \
	srcs/parser/f_mat.c \
	srcs/parser/f_parse_cam.c \
	srcs/parser/f_parse_color.c \
	srcs/parser/f_parse_grad.c \
	srcs/parser/f_parse_light.c \
	srcs/parser/f_parse_loc.c \
	srcs/parser/f_parse_obj.c \
	srcs/parser/f_parse_prst.c \
	srcs/parser/f_parse_scene.c \
	srcs/parser/f_parser.c \
	srcs/parser/f_wrong_type.c \
	srcs/render/cast_light.c \
	srcs/render/moy_4_colors.c \
	srcs/render/r_antialiasing.c \
	srcs/render/r_filter.c \
	srcs/render/r_intercections.c \
	srcs/render/r_intersect.c \
	srcs/render/r_isptin.c \
	srcs/render/r_normals.c \
	srcs/render/r_perlin_noise.c \
	srcs/render/r_phong.c \
	srcs/render/r_proc_texture.c \
	srcs/render/r_raytrace.c \
	srcs/render/r_refraction.c \
	srcs/render/r_render.c \
	srcs/render/r_shape_texture.c \
	srcs/render/r_texture_color.c \
	srcs/render/r_tools1.c \
	srcs/render/reslist.c \
	srcs/render/trans_line.c \
	srcs/render/trans_pt.c \
	srcs/render/trans_vec.c \
	srcs/texture/t_link_texture.c \
	srcs/utils.c

INCS = \
	./includes \
	/Library/Frameworks/SDL2.framework/Headers \
	libs/libft/includes \

MKES = libs/libft/
ARCH = libs/libft.a
ARCF = libs/libmlx.a
INCSDIR = $(addprefix -I,$(INCS))
INCSFILE = $(foreach d,$(INCS),$(wildcard $d/*.h))
OBJS = $(patsubst srcs/%.c,objs/%.o,$(SRCS))

DLLIST = $(addprefix -l,$(DL))

BLUE = \033[38;5;117m
RED = \033[38;5;203m
GREEN = \033[38;5;120m
VIOLET = \033[38;5;135m
WHITE = \033[37m

all:
	make -C libs/libft/
	@make $(NAME)

$(NAME): $(OBJS) $(ARCH)
	@$(CC) $(FLAGS) $(FWL) $(DLLIST) $(ARCF) $^ -o $@
	@printf "$(VIOLET)%15s : $(GREEN)succesfuly made!%20.0d\n" $(NAME) 0

objs/%.o: srcs/%.c $(INCSFILE)
	@[ -d $(dir $@) ] || (mkdir -p $(dir $@) && printf "$(VIOLET)%15s : $(WHITE)mkdir: %s\n" $(NAME) $(dir $@))
	@printf "$(VIOLET)%15s : $(BLUE)%-20s$(WHITE) ...\r" $(NAME) $(<F)
	@$(CC) -c -o $@ $(FLAGS) $(INCSDIR) $<
	@printf "$(VIOLET)%15s : $(BLUE)%-20s$(GREEN) done$(WHITE)\n" $(NAME) $(<F)

clean:
	@$(foreach p,$(MKES),make -C $(p) clean;)
	@[ -d "./objs" ] && rm -rf objs && printf "$(VIOLET)%15s : $(RED)objs destroyed\n" $(NAME) || printf "$(VIOLET)%15s : $(BLUE)object files not found\n" $(NAME)

tclean:
	@$(foreach p,$(MKES),make -C $(p) tclean;)
	@[ -f $(NAME) ] && rm -rf $(NAME) && printf "$(VIOLET)%15s : $(RED)%s destroyed\n" $(NAME) $(NAME) || printf "$(VIOLET)%15s : $(BLUE)Target file %s not found\n" $(NAME) $(NAME)

fclean: clean tclean
	@printf "\n"

re: fclean all

.PHONY: re fclean tclean clean debug all
