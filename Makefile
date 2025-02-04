NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_init.c ft_monitor.c ft_routine_cont.c ft_routine.c ft_threads.c ft_time.c ft_utils.c main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)

re: fclean all