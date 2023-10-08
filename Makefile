SRCS    =	main.c \
			ft_atoi.c \
			init.c \
			sleep.c \
			eat.c \
			utils.c \
			philo_sleep.c \
			think.c \
			death.c

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

re: fclean all

.PHONY: all clean fclean compile c C re