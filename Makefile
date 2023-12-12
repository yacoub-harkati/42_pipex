CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = pipex.c pipex_utils.c pipex_utils_2.c
SRC_BONUS = pipex_bonus.c pipex_utils.c pipex_utils_2.c
SRCS = $(addprefix ./src/, $(SRC))
SRCS_BONUS = $(addprefix ./src/, $(SRC_BONUS))

OBJS = $(SRC:.c=.o)
OBJS_BONUS = $(SRC_BONUS:.c=.o)
LIBFT = ./libft/libft.a
HEAD = ./includes
NAME = pipex
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) -c $(SRCS) -I $(HEAD)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -I $(HEAD)

bonus: $(BONUS_OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) -c $(SRCS_BONUS) -I $(HEAD)
	@$(CC) $(CFLAGS) -o $(NAME) $(BONUS_OBJS) $(LIBFT) -I $(HEAD)

$(BONUS_OBJS):
	make -C libft
	@$(CC) $(CFLAGS) -c $(BONUS_SRCS) -I $(HEAD)

fclean: clean
	@make fclean -C libft
	@$(RM) $(NAME)

clean:
	@make clean -C libft
	@$(RM) $(OBJS) $(BONUS_OBJS)

re: fclean all

.PHONY: clean fclean all re
