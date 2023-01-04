SRCS			= forks.c philo_behaviour.c philo.c sem_func.c utils.c
RM				= rm -f
GCC			= gcc -Wall -Wextra -Werror

FLAGS_DATARACE	=	-fsanitize=thread -g
FLAGS_MEMORY	=	-fsanitize=address -g
NAME		= philo
all:			$(SRCS) $(NAME)

$(NAME): $(SRCS)
	@reset
	$(GCC) $(SRCS) -o $(NAME)

clean:
	$(RM) $(NAME)

fclean:			clean
	@echo "cleaning 100%"

re:				fclean $(NAME)


.PHONY:			all clean fclean re