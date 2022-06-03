NAME = philo
SRCS = main.c
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror
DEBUG = -g -fsanitize=address -fsanitize=undefined -fsanitize=leak -fsanitize=memory

$(NAME): $(OBJS)
	gcc $(FLAGS) $(OBJS) $(DEBUG) -o $(NAME)

all: $(NAME)

fclean:
	rm -f $(NAME) $(OBJS)
	@echo "Cleaned.\n"
	
re: fclean all

.PHONY: all fclean re
