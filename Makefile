# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 23:17:29 by kbossio           #+#    #+#              #
#    Updated: 2025/01/29 21:18:12 by kbossio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minitalk
CC = gcc -Wall -Wextra -Werror
SRCS= client.c server.c
OBJS= $(SRCS:.c=.o)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): client server

all: $(NAME)

client: client.o
	$(CC) client.o -o client

server: server.o
	$(CC) server.o -o server

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f client server

re: fclean all

.PHONY: all clean fclean re