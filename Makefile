CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g -I./Libft -fsanitize=address -g3

SRCS =	main.c \
		parsing/parser.c\
		parsing/parser_utils.c\
		parsing/token_utils.c\
		parsing/utility_functions.c\
		parsing/lexer_utils.c\
		parsing/lexer_check.c\
		parsing/lexer_metachar.c\
		parsing/lexer_tokenize.c\
		parsing/env_utils.c\
		parsing/env.c\
		parsing/init.c\


OBJS = $(SRCS:.c=.o)

all: libft $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) ./Libft/libft.a -lreadline

libft:
		make -C ./Libft

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
