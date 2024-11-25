NAME = libft.a
CFLAGS = -Wall -Werror -Wextra
SRC = ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c
SRCBONUS = ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstmap_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c
OBJDIR = objs/
OBJ = $(SRC:.c=.o)
OBJBONUS = $(SRCBONUS:.c=.o)
OBJS_PATH = $(addprefix $(OBJDIR), $(OBJ))
OBJS_PATHB = $(addprefix $(OBJDIR), $(OBJBONUS))

$(NAME):	$(OBJS_PATH)
			@ar rc $(NAME) $(OBJS_PATH)

bonus:		$(OBJS_PATH) $(OBJS_PATHB)
			@ar rc $(NAME) $(OBJS_PATH) $(OBJS_PATHB)

all:		$(NAME)

$(OBJDIR)%.o: %.c | $(OBJDIR)
			@mkdir -p $(dir $@)
			@cc -c $< -o $@ $(CFLAGS)
			@if [ "$(filter $<,$(SRC))" ]; then $(MAKE) progress; fi

$(OBJDIR):
			@mkdir -p $(OBJDIR)

progress:
			@$(eval PROGRESS := $(shell echo $$(($(shell find $(SRC) -name '*.c' | wc -l) - $$(find $(OBJDIR) -name '*.o' | wc -l)))))
			@$(eval TOTAL := $(shell find $(SRC) -name '*.c' | wc -l))
			@$(eval PERCENT := $(shell echo "scale=2; (1 - $(PROGRESS) / $(TOTAL)) * 100" | bc))
			@$(eval BAR := $(shell printf '=%.0s' {1..$(shell echo "scale=0; $(PERCENT) / 2" | bc)}))
			@printf "\r[%-50s] %s%%" "$(BAR)" "$(PERCENT)"
			@if [ "$(PERCENT)" = "100.00" ]; then printf "\n"; fi
			@if [ "$(PERCENT)" = "100.00" ]; then printf "\033[0;32mlibft compiled\033[0m\n"; fi

clean:
			@rm -rf $(OBJDIR)

fclean:		clean
			@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus progress