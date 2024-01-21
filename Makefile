NAME = pipex

LIBFT = libft.a

LIBFT_DIR = libft/

SRCS = pipex.c pipex_utils.c

SRCS_BONUS = pipex_bonus.c pipex_utils_bonus.c pipex_heredoc_bonus.c pipex_exec_bonus.c

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(SRCS_BONUS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(LIBFT) $(NAME)

bonus: $(LIBFT) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT_DIR)$(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT) -o $(NAME)


clean:
	make -C $(LIBFT_DIR) clean
	rm -f *.o

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f pipex

re: fclean all

.PHONY: all clean fclean re