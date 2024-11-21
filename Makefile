NAME = miniRT
CC = cc
CFLAGS = \
			-I inc \
			-I lib/libft \
			-I lib/get_next_line \
			-I lib/mlx/include

SRCS = $(shell find src -name '*.c')
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
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS) -fsanitize=address

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
