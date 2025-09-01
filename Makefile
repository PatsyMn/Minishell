CC = cc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g -I./Libft -fsanitize=address -g3

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a
OBJ_DIR = obj

SRCS = main.c \
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
	parsing/quote_utils.c\
	parsing/init.c\
	parsing/parser_redirections.c\

OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: parsing/%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -s -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
