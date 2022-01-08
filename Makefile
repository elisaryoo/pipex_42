# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/05 20:52:43 by eryoo             #+#    #+#              #
#    Updated: 2022/01/08 19:00:33 by eryoo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= pipex
CC = gcc
FLAGS = -Wall -Wextra -Werror
BIN = /bin/rm -rf
MFLAGS = -g -fsanitize=address

INCLUDES = include/pipex.h

SRCS= srcs/pipex.c \
		srcs/pipex_utils.c \
		srcs/pipex_utils_two.c \
		srcs/pipex_execution.c

OBJS = $(SRCS:.c=.o)

all: $(NAME) $(INCLUDE)

$(NAME): $(OBJS)
		@$(CC) $(FLAGS) $(MFLAGS) -o $(NAME) $(OBJS)

clean:
		@$(RM) $(OBJS)

fclean: 
		@$(RM) $(OBJS)
		@$(RM) $(NAME)

norminette:
		norminette include srcs 

re: 
	fclean all

.PHONY: all clean fclean re