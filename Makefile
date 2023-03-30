SRCS += main.c
SRCS += utils.c
SRCS += free.c

OBJS = ${SRCS:.c=.o}

NAME = philo

GCC = cc

FLAGS = -Wall -Werror -Wextra

all: ${NAME}

.c.o:
	${GCC} -g ${FLAGS} -c -I. $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${GCC} ${FLAGS} ${OBJS} -o ${NAME}