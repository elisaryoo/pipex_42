# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eryoo <eryoo@student.42sp.org.br>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/05 20:52:43 by eryoo             #+#    #+#              #
#    Updated: 2022/01/09 11:46:32 by eryoo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= pipex
CC = gcc
FLAGS = -Wall -Wextra -Werror
BIN = /bin/rm -rf

INCLUDES = include/pipex.h

SRCS= srcs/pipex.c \
		srcs/pipex_utils.c \
		srcs/pipex_utils_two.c \
		srcs/pipex_execution.c \
		srcs/pipex_execution_utils.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME) $(INCLUDE)

$(NAME): $(OBJS)
		@$(CC) $(FLAGS) -o $(NAME) $(OBJS)

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