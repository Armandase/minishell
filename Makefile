NAME		= minishell

SRCS		= main.c\
			  builtins/env.c builtins/pwd.c builtins/export.c builtins/var_env.c\
			  builtins/unset.c builtins/utils.c builtins/print_args.c builtins/cd.c\
			  builtins/echo.c builtins/exit.c builtins/export_utils.c\
			  builtins/var_utils.c builtins/export_append.c\
			  parsing/parsing.c parsing/parsing_utils.c\
			  parsing/parsing_special_utils.c parsing/split_token.c \
			  parsing/str_get_token.c parsing/stack_func.c\
			  parsing/quote_utils.c parsing/split_token_1.c\
			  parsing/split_utils.c parsing/quote_in_split.c \
			  execution/exec_cmd.c execution/execution.c execution/find_path.c \
			  execution/exec_utils.c execution/signals_handlers.c\
			  execution/exit.c execution/heredoc.c\
			  execution/builtins_execution.c execution/fd_manager.c\
			  execution/heredoc_utils.c execution/open_close_utils.c \

CC			= @clang
LIBS        = -Llibft -lft -lreadline
CFLAGS		= -Wall -Werror -Wextra
OBJS		= ${SRCS:.c=.o}

all: ${NAME}

.c.o :
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	@make -s -C libft --no-print-directory
	${CC} ${CFLAGS} -o ${NAME} ${SRCS} ${LIBS}
	@printf '\x1b[38;2;255;0;0m███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓   \n▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    \n▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    \n▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    \n▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒\n░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░\n░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░\n░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   \n       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░\x1b[0m\n'

clean:
	@rm -f ${OBJS}
	@printf '\e[5m❌ \e[0m\x1b[38;2;255;140;0mObjects removed\x1b[0m\e[5m ❌\n\e[0m'

fclean : clean
	@rm -f ${NAME}
	@printf '\e[5m🚨 \e[0m\x1b[38;2;200;0;20mBinary removed\x1b[0m\e[5m 🚨\n\e[0m'

re: fclean all

.PHONY: all clean fclean re
