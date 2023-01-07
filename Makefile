NAME		= minishell
SRCS		= *.c 
CC			= clang
LIBS        = -Llibft -lft
CFLAGS		= -Wall -Werror -Wextra -g
OBJS		= ${SRCS:.c=.o}

all: ${NAME}

$(NAME): ${OBJS}
	make -C ./libft
	${CC} ${CFLAGS} -o ${NAME} ${SRCS} ${LIBS}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
	make clean -C ./libft
	rm -f ${OBJS}

fclean : clean
	rm -f ${NAME}

re: fclean all

norm:
	norminette *.c && norminette *.h

.PHONY: all clean fclean re norm 
