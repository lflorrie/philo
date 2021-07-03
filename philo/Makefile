NAME=philo

CC=gcc
CFLAGS=-Wall -Werror -Wextra -pthread

SRC=main.c parser.c

OBJ=$(SRC:.c=.o)
DEP=$(SRC:.c=.d)

all:$(NAME)

%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) $< > $*.d

-include $(OBJ:.o=.d)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ) $(DEP)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re