NAME		= minishell
SRCS		= main.c\
			  builtins/env.c builtins/pwd.c builtins/export.c builtins/var_env.c\
			  builtins/unset.c builtins/utils.c builtins/print_args.c builtins/cd.c\
			  builtins/echo.c builtins/exit.c\
			  parsing/parsing.c \
			  parsing/parsing_utils.c parsing/split_token.c \
			  parsing/str_get_token.c parsing/stack_func.c\
			  execution/exec_cmd.c execution/execution.c execution/find_path.c \
			  execution/exec_utils.c execution/signals_handlers.c\
			  execution/exit.c execution/heredoc.c\

CC			= clang
LIBS        = -Llibft -lft -lreadline
CFLAGS		= -Wall -Werror -Wextra -g -gdwarf-4
OBJS		= ${SRCS:.c=.o}

all: ${NAME}

.c.o :
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	@make -C ./libft --no-print-directory
	@${CC} ${CFLAGS} -o ${NAME} ${SRCS} ${LIBS}
	@printf '\x1b[38;2;0;255;255m███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓   \n▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    \n▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    \n▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    \n▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒\n░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░\n░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░\n░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   \n       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░\x1b[0m\n'

clean:
	@rm -f ${OBJS}

fclean : clean
	@rm -f ${NAME}

re: fclean all

norm:
	norminette *.c && norminette *.h

vg:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=.vsupp ./minishell

.PHONY: all clean fclean re norm vg
