NAME = miniRT
CC = cc
CFLAGS = -Wall -Werror -Wextra\
			-I inc \
			-I lib/libft \
			-I lib/get_next_line \
			-I lib/mlx/include

SRC_FILES = \
	math/bump_mapping.c math/matrix.c math/transformation_1.c math/transformation_2.c \
	math/uv_coords.c math/vec_calc_1.c math/vec_calc_2.c math/vec_calc_3.c \
	parsing/check_file.c parsing/helper_2.c parsing/helper.c parsing/init_data.c parsing/parsing_helper_2.c \
	parsing/parsing_helper.c parsing/parsing_obj_helper.c parsing/parsing_obj.c parsing/parsing.c \
	shapes/cone_inter.c shapes/cone_utils.c shapes/cylinder_inter.c shapes/cylinder_utils.c \
	shapes/plane.c shapes/sphere.c \
	check_hit.c error.c error_2.c hooks.c img_creation.c key_actions.c main.c sampling.c shading.c shading_2.c

SRCS_DIR = src
OBJS_DIR = objs

SRCS = $(addprefix $(SRCS_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJS_DIR)/, $(SRC_FILES:.c=.o))


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

all:				$(NAME)

$(NAME):			$(OBJS) $(LIBFT) $(GET_NEXT_LINE) $(MLX)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

$(OBJS_DIR)/%.o:	src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

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

.PHONY:				all clean fclean re

