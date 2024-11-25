NAME = lib_get_next_line.a
CFLAGS = -Wall -Wextra -Werror

SRC = get_next_line.c \
	get_next_line_utils.c

OBJ = $(SRC:.c=.o)
OBJDIR = objs/
OBJS_PATH = $(addprefix $(OBJDIR), $(OBJ))

all:			$(NAME)

$(NAME):		$(OBJS_PATH)
				@ar rc $(NAME) $(OBJS_PATH)

$(OBJDIR)%.o: %.c | $(OBJDIR)
				@mkdir -p $(dir $@)
				@cc -c $< -o $@ $(CFLAGS)
				@$(MAKE) progress

$(OBJDIR):
				@mkdir -p $(OBJDIR)

progress:
				@$(eval PROGRESS := $(shell echo $$(($(shell find . -name '*.c' | wc -l) - $$(find $(OBJDIR) -name '*.o' | wc -l)))))
				@$(eval TOTAL := $(shell find . -name '*.c' | wc -l))
				@$(eval PERCENT := $(shell echo "scale=2; (1 - $(PROGRESS) / $(TOTAL)) * 100" | bc))
				@$(eval BAR := $(shell printf '=%.0s' {1..$(shell echo "scale=0; $(PERCENT) / 2" | bc)}))
				@printf "\r[%-50s] %s%%" "$(BAR)" "$(PERCENT)"
				@if [ "$(PERCENT)" = "100.00" ]; then printf "\n"; fi
				@if [ "$(PERCENT)" = "100.00" ]; then printf "\033[0;32mget_next_line compiled\033[0m\n"; fi


clean:
				@rm -rf $(OBJDIR)

fclean:			clean
				@rm -f $(NAME)

re:				fclean all

.PHONY: all clean fclean re progress