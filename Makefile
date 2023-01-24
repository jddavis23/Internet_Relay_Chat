# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdavis <jdavis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 16:27:42 by jdavis            #+#    #+#              #
#    Updated: 2023/01/24 17:16:00 by jdavis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
CLI = client

CC = c++ -Wall -Wextra -Werror -std=c++98

SRC = irc.cpp
#SRC += Array.tpp
SRCCL = client.cpp

OBJS := ${SRCS:c=o} 

all:	$(NAME) $(CLI)

$(NAME): $(SRC)
	$(CC) -o $(NAME) $(SRC)

$(CLI): $(SRCCL)
	$(CC) -o $(CLI) $(SRCCL)


#clean:
#	rm $(OBJS)

fclean: #clean
	rm $(NAME)
	rm $(CLI)

re: fclean all 