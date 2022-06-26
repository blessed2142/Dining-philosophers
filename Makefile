SRCS	=	./philo/error.c ./philo/ft_parcer.c ./philo/life.c ./philo/philosophers.c ./philo/utils.c ./philo/utils2.c

SRCS_BONUS	=	./philo_bonus/error.c ./philo_bonus/ft_parcer.c ./philo_bonus/ft_parcer2.c ./philo_bonus/philosophers_bonus.c ./philo_bonus/utils.c ./philo_bonus/utils2.c

OBJS	= 	$(SRCS:.c=.o)

OBJS_BONUS	= 	$(SRCS_BONUS:.c=.o)

NAME	=	philosophers

NAME_BONUS		=	philosophers_bonus

GCC		= 	gcc

RM		= 	rm -f

CFLAGS	= 	-Wall -Wextra -Werror

all:		$(NAME)

bonus:		$(NAME_BONUS)

%.o:		%.c		
			$(GCC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) ./philo/philosophers.h
			$(GCC) $(OBJS) -o $(NAME)

$(NAME_BONUS):	$(OBJS_BONUS) ./philo_bonus/philosophers_bonus.h
			$(GCC) $(OBJS_BONUS) -o $(NAME_BONUS)

clean:		
			$(RM) $(OBJS)
			$(RM) $(OBJS_BONUS)

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(NAME_BONUS)

re:			fclean all

.PHONY:		all clean fclean re