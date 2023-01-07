NAME		= minishell
SRCS		= main.c\
			  builtins/env.c\

CC			= clang
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

.PHONY: all clean fclean re norm 
