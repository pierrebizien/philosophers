SRCS += main.c
SRCS += utils.c
SRCS += free.c
SRCS += print.c
SRCS += parsing.c
SRCS += ft_atoi.c

OBJS = ${SRCS:.c=.o}

NAME = philo

GCC = cc

FLAGS = -Wall -Werror -Wextra

all: ${NAME}

.c.o:
	${GCC} -g ${FLAGS} -c -I -pthread $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${GCC} ${FLAGS} -pthread ${OBJS} -o ${NAME}

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all