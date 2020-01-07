# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fberger <fberger@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/07 17:41:37 by fberger           #+#    #+#              #
#    Updated: 2020/01/07 18:43:59 by fberger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror

SRCS = srcs/main.c # srcs/builtins/*.c srcs/executables/*.c

OBJS = ${SRCS:.c=.o}

LIBS = -L. libftprintf.a

HEADER = -I ./includes/

all: $(NAME)

.c.o:
	gcc $(FLAGS) $(HEADER) -c $< -o $@

$(NAME): $(OBJS)
	gcc $(OBJS) -o $(NAME) $(LIBS)

clean:
	rm -f srcs/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
