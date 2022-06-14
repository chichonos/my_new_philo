NAME = philo
SRCS = main.c init.c dinner.c parsing.c time.c utils.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror
DEBUG = -g -fsanitize=address

BLACK			:=	"\033[1;30m"
RED				:=	"\033[1;31m"
GREEN			:=	"\033[1;32m"
PURPLE			:=	"\033[1;35m"
BLUE			:=	"\033[1;36m"
WHITE			:=	"\033[1;37m"
EOC				:=	"\033[0;0m"

$(NAME): $(OBJS)
	gcc $(CFLAGS) $(OBJS) $(DEBUG) -o $(NAME)
	@echo $(GREEN) "Compiled." $(EOC)

all: $(NAME)

clean:
	-@rm -rf $(OBJS) 2>/dev/null || true
	@echo $(GREEN) "Cleaned all *.o files." $(EOC)

fclean:
	rm -f $(NAME) $(OBJS)
	@echo $(PURPLE) "Cleaned.\n" $(EOC)
	
re: fclean all

.PHONY: all fclean re
