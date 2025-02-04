# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bekarada <bekarada@student.42istanbul.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 07:21:26 by hugozlu           #+#    #+#              #
#    Updated: 2025/02/04 18:58:17 by bekarada         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
SRCS = main.c ft_utils.c ft_actions.c ft_thread.c ft_mutex.c\
	ft_monitor.c ft_init.c ft_time.c ft_inform.c ft_check.c
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
