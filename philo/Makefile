# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/08 10:50:48 by lflorrie          #+#    #+#              #
#    Updated: 2021/07/08 10:50:49 by lflorrie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo

CC=gcc
CFLAGS=-Wall -Werror -Wextra -pthread

SRC=main.c \
	parser.c \
	philo.c \
	utils.c

INC=philo.h
OBJ=$(SRC:.c=.o)

all:$(NAME)

%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME):$(OBJ) $(INC)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ) $(DEP)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
