# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fberger <fberger@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/07 17:41:37 by fberger           #+#    #+#              #
#    Updated: 2020/01/15 17:37:43 by fberger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= minishell

CC		= gcc

FLAGS 	= -Wall -Wextra -Werror

SRCS 	= srcs/main.c \
		srcs/builtins/echo.c srcs/builtins/cd.c srcs/builtins/env.c \
		srcs/builtins/pwd.c \
		srcs/executables/exec.c \
		srcs/utils/free.c srcs/utils/utils.c srcs/utils/signal.c

OBJS 	= ${SRCS:.c=.o}

LIB 	= -L. libft/libft.a

HEADER 	= -I ./includes/

all: $(NAME)

.c.o:
	@gcc $(FLAGS) $(HEADER) -c $< -o $@

$(NAME): $(OBJS)
	# @make -C libft
	@gcc $(OBJS) -o $(NAME) $(LIB)

clean:
	@/bin/rm -f $(OBJS)
	# @make clean -C libft

fclean: clean
	@/bin/rm -f $(NAME)
	# @make fclean -C libft

re: fclean all
