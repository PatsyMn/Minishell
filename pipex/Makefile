NAME_MANDATORY = pipex
NAME_BONUS = pipex_bonus

CFLAGS = -Wall -Wextra -Werror -g3

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = execute_cmd.c \
open_file.c \
pipe_handle.c
SRC_MANDATORY = main_mandatory.c
SRC_BONUS = main_bonus.c \
read_heredoc_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_MANDATORY = $(SRC_MANDATORY:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(LIBFT) $(NAME_MANDATORY) $(NAME_BONUS)

mandatory: $(LIBFT) $(NAME_MANDATORY)

bonus: $(LIBFT) $(NAME_BONUS)

$(NAME_MANDATORY): $(OBJ) $(OBJ_MANDATORY) $(LIBFT)
	cc ${CFLAGS} -o $(NAME_MANDATORY) $(OBJ) $(OBJ_MANDATORY) $(LIBFT)
	@touch infile

$(NAME_BONUS): $(OBJ) $(OBJ_BONUS) $(LIBFT)
	cc ${CFLAGS} -o $(NAME_BONUS) $(OBJ) $(OBJ_BONUS) $(LIBFT)
	@touch infile

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) > /dev/null

%.o: %.c
	cc -c ${CFLAGS} -o $@ $<

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f *.o

fclean: clean
	$(MAKE) fclean -s -C $(LIBFT_DIR)
	rm -f $(NAME_MANDATORY) $(NAME_BONUS) libft.a
	@rm -f infile outfile

re: fclean all

.PHONY: all mandatory bonus fclean clean re