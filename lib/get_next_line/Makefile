NAME = lib_get_next_line.a
CFLAGS = -Wall -Wextra -Werror

SRC = get_next_line.c \
	get_next_line_utils.c

OBJ = $(SRC:.c=.o)
OBJB = $(SRCB:.c=.o)
OBJDIR = objs/
OBJS_PATH = $(addprefix $(OBJDIR), $(OBJ))

all:			$(NAME)

$(NAME):		$(OBJS_PATH)
				@ar rc $(NAME) $(OBJS_PATH)

$(OBJDIR)%.o: %.c
				@mkdir -p $(dir $@)
				@cc -c $< -o $@ $(CFLAGS)

clean:
				@rm -rf $(OBJDIR)

fclean:			clean
				@rm -f $(NAME)