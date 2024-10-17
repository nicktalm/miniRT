RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
NC = \033[0m
CLEAR_LINE = \033[2K\r

NAME = miniRT
BONUS_NAME = miniRT_Bonus
CXX = cc
# CXXFLAGS = -Wall -Wextra -Werror
SRCDIR = ./src
OBJDIR = ./obj
SRC = $(addprefix $(SRCDIR)/, main.c shading.c plane.c sphere.c matrix.c transformation.c cylinder.c check_hit.c multi_threading.c img_creation.c init_data.c key_actions.c vec_calc.c check_file.c error.c parsing.c helper.c parsing_obj.c parsing_helper.c helper_2.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TOTAL_FILES = $(words $(SRC))
CURRENT = 0
LIBFT = lib/libft
GET_NEXT = lib/get_next_line
MLX = lib/mlx
INLIBFT = -L $(LIBFT) -lft
INGET_NEXT = -L $(GET_NEXT) -l_get_next_line
INMLX = -L $(MLX)/build -lmlx42 -ldl -L /usr/local/lib/ -lglfw -pthread -lm

# /opt/homebrew/Cellar/glfw/3.3.8/lib/
all: $(NAME)

$(NAME): $(OBJ)
	@cd $(LIBFT) && $(MAKE) bonus
	@cd $(GET_NEXT) && $(MAKE) all
	@printf "\n"
	cmake $(MLX) -B $(MLX)/build && make -C $(MLX)/build -j4
	@$(CXX) $(CXXFLAGS) $(INMLX) $(INGET_NEXT) $(INLIBFT) -o $(NAME) $(OBJ) -fsanitize=address
	@if [ -f $(NAME) ]; then\
		echo "$(GREEN)\nCompilation successful! Executable $(NAME) created.$(NC)";\
	else\
		echo "$(RED)\nCompilation failed!$(NC)";\
	fi

bonus: $(OBJ)
	@cd $(LIBFT) && $(MAKE) bonus
	@cd $(GET_NEXT) && $(MAKE) all
	@printf "\n"
	cmake $(MLX) -B $(MLX)/build && make -C $(MLX)/build -j4
	@$(CXX) $(CXXFLAGS) $(INMLX) $(INGET_NEXT) $(INLIBFT) -o $(BONUS_NAME) $(OBJ) -fsanitize=address
	@if [ -f $(BONUS_NAME) ]; then\
		echo "$(GREEN)\nCompilation successful! Executable $(BONUS_NAME) created.$(NC)";\
	else\
		echo "$(RED)\nCompilation failed!$(NC)";\
	fi

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@$(eval CURRENT=$(shell expr $(CURRENT) + 1))
	@printf "$(CLEAR_LINE)"
	@printf "$(MAGENTA)Compiling $(NAME)... $(NC)"
	@printf "[ "
	@for number in `seq 1 $(TOTAL_FILES)`; do \
		if [ $$number -le $(CURRENT) ]; then \
			printf "$(GREEN)▓ $(NC)"; \
		else \
			printf "$(RED)░ $(NC)"; \
		fi; \
	done
	@printf "] $(BLUE)$(CURRENT)/$(TOTAL_FILES) ($(shell echo 'scale=2; $(CURRENT) * 100 / $(TOTAL_FILES)' | bc)%%)$(NC)"

clean:
	@clear
	@echo "$(RED)Cleaning up...$(NC)"
	@rm -rf $(OBJDIR)
	@cd $(LIBFT) && $(MAKE) clean
	@cd $(GET_NEXT) && $(MAKE) clean
	@rm -rf $(MLX)/build

fclean: clean
	@clear
	@echo "$(RED)Cleaning up...$(NC)"
	@echo "$(RED)Removing executable $(NAME)...$(NC)"
	@cd $(LIBFT) && $(MAKE) fclean
	@cd $(GET_NEXT) && $(MAKE) fclean
	@rm -f $(NAME)
	@echo "$(RED)Removing executable $(BONUS_NAME)...$(NC)"
	@rm -f $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus