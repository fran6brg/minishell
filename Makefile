# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fberger <fberger@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/07 17:41:37 by fberger           #+#    #+#              #
#    Updated: 2020/01/08 02:24:39 by fberger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRCS = srcs/main.c # srcs/builtins/*.c srcs/executables/*.c

OBJS = ${SRCS:.c=.o}

LIB = -L. libft/libft.a

HEADER = -I ./includes/

all: $(NAME)

.c.o:
	gcc $(FLAGS) $(HEADER) -c $< -o $@

$(NAME): $(OBJS)
	gcc $(OBJS) -o $(NAME) $(LIB)

libft:
	@make -C libft

clean:
	@/bin/rm -f $(OBJS)
	@make clean -C libft

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
