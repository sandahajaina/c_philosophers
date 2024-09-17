NAME = philo
SRCS = srcs/main.c srcs/init.c srcs/utils.c srcs/monitoring.c srcs/philosopher.c srcs/actions.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -pthread -g -c $< -o $@

valgrind : $(NAME)
	valgrind $(--leak-check=full --track-origins=yes --tool=helgrind) ./$(NAME) 200 5000 200 200 3

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
