SRC = main.c philo.c utils.c utils2.c
OBJ = $(SRC:%.c=%.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
PTHEAD_FLAG = -pthread

NAME = philo

$(NAME)	:	$(OBJ)
			$(CC) $(CFLAGS) $(PTHEAD_FLAG) $(OBJ) -o $(NAME)

all		:	$(NAME)

clean	:
			rm -f $(OBJ)

fclean	:	clean
			rm -f $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re