CC       = cc
HEADERS_DIR = .
NAME     = pipex
RM       = rm -rf

LIBFT_DIR = utils/
LIBFT = $(LIBFT_DIR)libft.a
# CFLAGS   = -Wall -Wextra -Werror -g3 -o3 -I $(HEADERS_DIR) -I $(LIBFT)
# CFLAGS   = -Wall -Wextra -Werror -g3 -o3 -fsanitize=address -I $(HEADERS_DIR) -I $(LIBFT_DIR)
CFLAGS   = -Wall -Wextra -Werror -g3 -o3  -I $(HEADERS_DIR) -I $(LIBFT_DIR)

CFILES = main.c \
		parsers.c \
		processes.c \
		error.c

OFILES = $(CFILES:.c=.o)

all: $(NAME)

# -L = library dir
# -lft = link the library.a
$(NAME): $(LIBFT) $(OFILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OFILES) -L $(LIBFT_DIR) -lft

# -C = execute the command in the following directory
$(LIBFT):
	make -C $(LIBFT_DIR)
clean:
	$(RM) $(OFILES)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
