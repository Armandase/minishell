NAME	= libft.a

SRCS	= ft_isalpha.c ft_memchr.c ft_putchar_fd.c \
		  ft_strchr.c ft_strlcpy.c ft_strrchr.c \
		  ft_isascii.c ft_memcmp.c ft_putendl_fd.c \
		  ft_strdup.c ft_strlen.c ft_strtrim.c \
		  ft_isdigit.c ft_memcpy.c ft_putnbr_fd.c \
		  ft_striteri.c ft_strmapi.c ft_substr.c \
		  ft_isprint.c ft_memmove.c ft_putstr_fd.c \
		  ft_strjoin.c ft_strncmp.c ft_tolower.c \
		  ft_itoa.c ft_memset.c ft_split.c \
		  ft_strlcat.c ft_strnstr.c ft_toupper.c \
		  ft_atoi.c ft_bzero.c ft_calloc.c \
		  ft_isalnum.c ft_lstdelone.c ft_lstiter.c \
		  ft_lstlast.c ft_lstmap.c ft_lstnew.c \
		  ft_lstsize.c ft_lstadd_front.c ft_lstclear.c \
		  ft_lstadd_back.c ft_fprint_addr.c ft_printf.c \
		  ft_putfchar.c ft_putfstr.c ft_putfnbr.c \
		  ft_putfnbr_base.c get_next_line.c get_next_line_utils.c \
		  ft_strcpy.c ft_strncpy.c ft_strtok.c

CC = clang

CFLAGS = -Wall -Werror -Wextra

OBJS = ${SRCS:.c=.o}

all: ${NAME}

$(NAME): ${OBJS}
	ar -rc ${NAME} ${OBJS}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
clean:
	@rm -f ${OBJS}
fclean : clean
	@rm -f ${NAME}
re: fclean all

.PHONY: all clean fclean re

