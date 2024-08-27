RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
NC = \033[0m
CLEAR_LINE = \033[2K\r

NAME = miniRT
CXX = cc
CXXFLAGS = -Wall -Wextra -Werror
SRCDIR = ./src
OBJDIR = ./obj
SRC = $(addprefix $(SRCDIR)/, main.c check_file.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TOTAL_FILES = $(words $(SRC))
CURRENT = 0
all: $(NAME)
$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)
	@if [ -f $(NAME) ]; then\
		echo "$(GREEN)\nCompilation successful! Executable $(NAME) created.$(NC)";\
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
fclean: clean
	@clear
	@echo "$(RED)Cleaning up...$(NC)"
	@echo "$(RED)Removing executable $(NAME)...$(NC)"
	@rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
