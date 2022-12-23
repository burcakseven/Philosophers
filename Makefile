SRCS			= philo.c utils.c philo_funcs.c behaviour_utils.c
RM				= rm -f
GCC			= gcc -Wall -Wextra -Werror
NAME			= philo

FLAGS_DATARACE	=	-fsanitize=thread -g
FLAGS_MEMORY	=	-fsanitize=address -g

all:			$(SRCS) $(NAME)

$(NAME): $(SRCS)
	@reset
	$(GCC) $(SRCS) -o $(NAME)

data_race: $(SRCS)
	@$(GCC) $(FLAGS_DATARACE) $(SRCS) -o philo_thread


memory_check: $(SRCS)
	@$(GCC) $(FLAGS_MEMORY) $(SRCS) -o philo_memory
	
clean:
	$(RM) $(NAME)

fclean:			clean
	@echo "cleaning 100%"

re:				fclean $(NAME)


.PHONY:			all clean fclean re