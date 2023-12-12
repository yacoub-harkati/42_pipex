CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ./src/pipex.c ./src/pipex_utils.c ./src/pipex_utils_2.c ./src/pipex_utils_3.c ./src/pipex_utils_4.c
SRC_BONUS = ./src/pipex_bonus.c ./src/pipex_utils.c ./src/pipex_utils_2.c ./src/pipex_utils_3.c ./src/pipex_utils_4.c

OBJS = $(SRC:.c=.o)
OBJS_BONUS = $(SRC_BONUS:.c=.o)
LIBFT = ./libft/libft.a
HEAD = ./includes
NAME = pipex
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC:.c=.o) $(LIBFT) -I $(HEAD)

bonus: $(OBJS_BONUS)
	@make -C libft
	@$(CC) $(CFLAGS) -o $(NAME)  $(SRC_BONUS:.c=.o) $(LIBFT) -I $(HEAD)

fclean: clean
	@make fclean -C libft
	@$(RM) $(NAME)

clean:
	@make clean -C libft
	@$(RM) $(OBJS) $(OBJS_BONUS)

re: fclean all

.PHONY: clean fclean all re
