SRCS    =	main.c \
			ft_atoi.c \
			init.c \
			

OBJS    = ${SRCS:.c=.o}
INCS    = includes
NAME    = philo
CC        = gcc
RM        = rm -rf
CFLAGS    = -Wall -Wextra -Werror -fsanitize=address -g

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${INCS}

${NAME}: ${OBJS}
	${CC} ${OBJS} ${CFLAGS} -o ${NAME}

all: ${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

compile:
	${CC} -fsanitize=address -g ${CFLAGS} -o ${NAME} ${SRCS} ${c} && ./push_swap 1 2 3

c:
	${RM} *.o printf/*.o 19_libft/*.o

C:
	${RM} ${c} push_swap push_swap.dSYM


re: fclean all

.PHONY: all clean fclean compile c C re