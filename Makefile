# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 23:17:29 by kbossio           #+#    #+#              #
#    Updated: 2025/03/27 13:29:55 by kbossio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
CC = cc -Wall -Wextra -Werror
SRCS = client.c server.c
OBJS = $(SRCS:.c=.o)
BSRCS = bonus/client_bonus.c bonus/server_bonus.c
BOBJS = $(BSRCS:.c=.o)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): client server

all: $(NAME)

client: client.o
	$(CC) client.o -o client

server: server.o
	$(CC) server.o -o server

clean:
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -f client server client_bonus server_bonus

re: fclean all

bonus: client_bonus server_bonus

client_bonus: $(BOBJS)
	$(CC) bonus/client_bonus.o -o client_bonus

server_bonus: $(BOBJS)
	$(CC) bonus/server_bonus.o -o server_bonus

.PHONY: all clean fclean re bonus

