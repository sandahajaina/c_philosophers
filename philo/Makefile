NAME = philo
SRCS = main.c init.c utils.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -pthread -g -c $< -o $@

leak : $(NAME)
	valgrind $(--leak-check=full --track-origins=yes --tool=helgrind) ./$(NAME) 50 400 200 200

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
