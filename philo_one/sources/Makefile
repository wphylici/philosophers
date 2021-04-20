NAME		=	philo_one

#HEADER		=	./includes/

CC			=	gcc

FLAGS		=	-g -Wall -Wextra -Werror

SRCS		=	./main.c ./utils.c

OBJS		=	$(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

re	:fclean all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

.PHONY: all clean fclean re
