CC       = cc
HEADERS_DIR = .
NAME     = pipex
NAME_BONUS = pipex_bonus
RM       = rm -rf

LIBFT_DIR = utils/
LIBFT = $(LIBFT_DIR)libft.a
CFLAGS   = -Wall -Wextra -Werror -g3 -o3 -I $(HEADERS_DIR) -I $(LIBFT_DIR)

BASE_MAIN = main.c
BONUS_MAIN = main_bonus.c

CFILES = parse_inputs.c \
		build_cmd_list.c \
		error.c \
		extract_path.c \
		pipes.c \
		processes.c \
		files_utils.c \

OFILES = $(CFILES:.c=.o)
O_BASE_MAIN = $(BASE_MAIN:.c=.o)
O_BONUS_MAIN = $(BONUS_MAIN:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(O_BASE_MAIN) $(OFILES)
	$(CC) $(CFLAGS) -o $(NAME) $(O_BASE_MAIN) $(OFILES) -L $(LIBFT_DIR) -lft

bonus: $(LIBFT) $(O_BONUS_MAIN) $(OFILES)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(O_BONUS_MAIN) $(OFILES) -L $(LIBFT_DIR) -lft

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
