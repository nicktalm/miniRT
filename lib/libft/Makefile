# NAME = libft.a
# CFLAGS = -Wall -Werror -Wextra
# SRC = ft_atoi.c \
# 		ft_bzero.c \
# 		ft_calloc.c \
# 		ft_isalnum.c \
# 		ft_isalpha.c \
# 		ft_isascii.c \
# 		ft_isdigit.c \
# 		ft_isprint.c \
# 		ft_itoa.c \
# 		ft_memchr.c \
# 		ft_memcmp.c \
# 		ft_memcpy.c \
# 		ft_memmove.c \
# 		ft_memset.c \
# 		ft_putchar_fd.c \
# 		ft_putendl_fd.c \
# 		ft_putnbr_fd.c \
# 		ft_putstr_fd.c \
# 		ft_split.c \
# 		ft_strchr.c \
# 		ft_strdup.c \
# 		ft_striteri.c \
# 		ft_strjoin.c \
# 		ft_strlcat.c \
# 		ft_strlcpy.c \
# 		ft_strlen.c \
# 		ft_strmapi.c \
# 		ft_strncmp.c \
# 		ft_strnstr.c \
# 		ft_strrchr.c \
# 		ft_strtrim.c \
# 		ft_substr.c \
# 		ft_tolower.c \
# 		ft_toupper.c
# SRCBONUS = ft_lstadd_back_bonus.c \
# 		ft_lstadd_front_bonus.c \
# 		ft_lstclear_bonus.c \
# 		ft_lstdelone_bonus.c \
# 		ft_lstiter_bonus.c \
# 		ft_lstlast_bonus.c \
# 		ft_lstmap_bonus.c \
# 		ft_lstnew_bonus.c \
# 		ft_lstsize_bonus.c
# OBJDIR = objs/
# OBJ = $(SRC:.c=.o)
# OBJBONUS = $(SRCBONUS:.c=.o)
# OBJS_PATH = $(addprefix $(OBJDIR), $(OBJ))
# OBJS_PATHB = $(addprefix $(OBJDIR), $(OBJBONUS))

# $(NAME):	$(OBJS_PATH)
# 			@ar rc $(NAME) *.o

# bonus:		$(OBJS_PATH) $(OBJS_PATHB)
# 			@ar rc $(NAME) *.o


# all:		$(NAME)

# $(OBJDIR): %.o:%.c
# 			@mkdir -p $(dir $@)
# 			@cc -c $< -o $@ $(CFLAGS)

# clean:
# 			@rm -f *.o

# fclean:		clean
# 			@rm -f $(NAME)

# re: fclean all

# .PHONY: all clean fclean re bonus
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

$(OBJDIR)%.o: %.c
			@mkdir -p $(OBJDIR)
			@cc -c $< -o $@ $(CFLAGS)

clean:
			@rm -rf $(OBJDIR)

fclean:		clean
			@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
