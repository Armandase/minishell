NAME		= minishell
SRCS		= main.c\
			  builtins/env.c builtins/pwd.c builtins/export.c builtins/var_env.c\
			  parsing/parsing.c parsing/strtok_unquote.c \
			  parsing/parsing_utils.c parsing/split_token.c \
			  parsing/str_get_token.c \
			  execution/exec_cmd.c execution/execution.c execution/find_path.c \
			  execution/exec_utils.c execution/signals_handlers.c

CC			= gcc
LIBS        = -Llibft -lft -lreadline
CFLAGS		= -Wall -Werror -Wextra -g
OBJS		= ${SRCS:.c=.o}

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	make -C ./libft
	${CC} ${CFLAGS} -o ${NAME} ${SRCS} ${LIBS}

clean:
	make clean -C ./libft
	rm -f ${OBJS}

fclean : clean
	rm -f ${NAME}

re: fclean all

norm:
	norminette *.c && norminette *.h

vg:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=.vsupp --trace-children=yes ./${NAME}

.PHONY: all clean fclean re norm 
