NAME = philo
SRCS = main.c init.c dinner.c parsing.c time.c utils.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror
DEBUG = -g -fsanitize=address

$(NAME): $(OBJS)
	gcc $(CFLAGS) $(OBJS) $(DEBUG) -o $(NAME)



all: $(NAME)

fclean:
	rm -f $(NAME) $(OBJS)
	@echo "Cleaned.\n"
	
re: fclean all

.PHONY: all fclean re
