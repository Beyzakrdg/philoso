NAME = philo
CC = cc
SRCS = main.c ft_utils.c ft_actions.c ft_thread.c ft_destroy.c\
	ft_prog.c ft_init.c ft_time.c ft_inform.c ft_check.c
CFLAGS = -Wall -Wextra -Werror
OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} -o ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}
re: fclean all
