NAME = miniRT
CC = cc
CFLAGS = -Wall -Werror -Wextra\
			-I inc \
			-I lib/libft \
			-I lib/get_next_line \
			-I lib/mlx/include

# Liste aller .c-Dateien
SRCS = src/math/bump_mapping.c src/math/matrix.c src/math/transformation_1.c src/math/transformation_2.c \
	src/math/uv_coords.c src/math/vec_calc_1.c src/math/vec_calc_2.c src/math/vec_calc_3.c \
	src/parsing/check_file.c src/parsing/helper_2.c src/parsing/helper.c src/parsing/init_data.c src/parsing/parsing_helper_2.c \
	src/parsing/parsing_helper.c src/parsing/parsing_obj_helper.c src/parsing/parsing_obj.c src/parsing/parsing.c \
	src/shapes/cone_inter.c src/shapes/cone_utils.c src/shapes/cylinder_inter.c src/shapes/cylinder_utils.c \
	src/shapes/plane.c src/shapes/sphere.c \
	src/check_hit.c src/error.c src/error_2.c src/hooks.c src/img_creation.c src/key_actions.c src/main.c src/sampling.c src/shading.c src/shading_2.c

OBJS_DIR = objs
OBJS = $(patsubst src/%.c, $(OBJS_DIR)/%.o, $(SRCS))

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

GET_NEXT_LINE_DIR = lib/get_next_line
GET_NEXT_LINE = $(GET_NEXT_LINE_DIR)/lib_get_next_line.a

MLX_DIR = lib/mlx
MLX = $(MLX_DIR)/build/libmlx42.a

LDFLAGS =  -L $(LIBFT_DIR) -lft \
			-L $(GET_NEXT_LINE_DIR) -l_get_next_line \
			-L $(MLX_DIR)/build -lmlx42 \
			-L /usr/local/lib/ -lglfw \
			-framework Cocoa -framework OpenGL -framework IOKit

# /opt/homebrew/Cellar/glfw/3.3.8/lib/
all:				$(NAME)

$(NAME):			$(OBJS) $(LIBFT) $(GET_NEXT_LINE) $(MLX)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

$(OBJS_DIR)/%.o: src/%.c | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(MAKE) progress

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

progress:
	$(eval PROGRESS := $(shell echo $$(($(shell find $(SRCS) -name '*.c' | wc -l) - $$(find $(OBJS_DIR) -name '*.o' | wc -l)))))
	$(eval TOTAL := $(shell find $(SRCS) -name '*.c' | wc -l))
	$(eval PERCENT := $(shell echo "scale=2; (1 - $(PROGRESS) / $(TOTAL)) * 100" | bc))
	$(eval BAR := $(shell printf '=%.0s' {1..$(shell echo "scale=0; $(PERCENT) / 2" | bc)}))
	@printf "\r[%-50s] %s%%" "$(BAR)" "$(PERCENT)"
	@if [ "$(PERCENT)" = "100.00" ]; then printf "\n"; fi
	@if [ "$(PERCENT)" = "100.00" ]; then printf "\033[0;32mminiRT compiled\033[0m\n"; fi

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(GET_NEXT_LINE):
	@$(MAKE) -C $(GET_NEXT_LINE_DIR)

$(MLX):
	@cmake -S $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

clean:
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(GET_NEXT_LINE_DIR) clean
	@rm -rf $(MLX_DIR)/build

fclean:				clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(GET_NEXT_LINE_DIR) fclean

re:					fclean all

.PHONY:				all clean fclean re progress