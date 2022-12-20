SRCS			= philo.c utils.c
RM				= rm -f
GCC			= gcc -Wall -Wextra -Werror
NAME			= philo
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