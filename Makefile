CC       = cc
HEADERS_DIR = .
NAME     = pipex
RM       = rm -rf

LIBFT_DIR = utils/
LIBFT = $(LIBFT_DIR)libft.a
# CFLAGS   = -Wall -Wextra -Werror -g3 -o3 -I $(HEADERS_DIR) -I $(LIBFT_DIR)
CFLAGS   = -Wall -Wextra -Werror -g3 -o3 -fsanitize=address -I $(HEADERS_DIR) -I $(LIBFT_DIR)


CFILES = main.c \
		parse_inputs.c \
		build_cmd_list.c \
		error.c \
		extract_path.c \
		pipes.c \
		processes.c \
		files_utils.c \

OFILES = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(O_BASE_MAIN) $(OFILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OFILES) -L $(LIBFT_DIR) -lft


$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OFILES)
	$(RM) $(O_BASE_MAIN) $(O_BONUS_MAIN)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean $(NAME) $(NAME_BONUS)

.PHONY: all clean fclean re bonus
