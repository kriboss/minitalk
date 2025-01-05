# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 23:17:29 by kbossio           #+#    #+#              #
#    Updated: 2025/01/05 23:20:24 by kbossio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minitalk.a
SRCS= client.c server.c
OBJS= $(SRCS:.c=.o)

%.o:%.c
	gcc -Wall -Wextra -Werror -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re