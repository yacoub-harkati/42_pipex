CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = 	ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
		ft_isprint.c ft_toupper.c ft_tolower.c ft_strlen.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_strnstr.c ft_strlcat.c ft_strlcpy.c \
		ft_strjoin.c ft_bzero.c ft_memset.c ft_memcpy.c ft_memmove.c ft_memchr.c \
		ft_memcmp.c ft_calloc.c ft_substr.c ft_strdup.c ft_strtrim.c ft_split.c ft_itoa.c \
		ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_atoi.c get_next_line.c ft_printf.c \

OBJS = $(SRCS:.c=.o)
BONUS_SRCS =	ft_lstnew_bonus.c ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c \
				ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
				ft_lstmap_bonus.c ft_lstsize_bonus.c ft_lstclear_bonus.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
HEAD = ./
NAME = libft.a
AR = ar rcs
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

bonus: $(BONUS_OBJS)

$(BONUS_OBJS):
	@$(CC) $(CFLAGS) -c $(BONUS_SRCS) -I $(HEAD)
	@$(AR) $(NAME) $(BONUS_OBJS)

fclean: clean
	@$(RM) $(NAME)

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)

re: fclean all

.PHONY: clean fclean all re
