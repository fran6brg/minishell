# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fberger <fberger@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/07 17:41:37 by fberger           #+#    #+#              #
#    Updated: 2020/02/01 04:03:40 by fberger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 	minishell

CC		= 	gcc

FLAGS 	= 	-Wall -Wextra -Werror -g

SRCS 	= 	srcs/main.c \
			srcs/builtins/single_builtin.c \
			srcs/builtins/echo.c \
			srcs/builtins/echo_utils.c \
			srcs/builtins/cd.c \
			srcs/builtins/env.c \
			srcs/builtins/env_utils.c \
			srcs/builtins/pwd.c \
			srcs/builtins/exit.c \
			srcs/exec/single_execv.c \
			srcs/exec/path.c \
			srcs/exec/exec_utils.c \
			srcs/root/process.c \
			srcs/utils/args.c \
			srcs/utils/fd.c \
			srcs/utils/free.c \
			srcs/utils/helpers.c \
			srcs/utils/signal.c \
			srcs/parsing/errors.c \
			srcs/parsing/split_1.c \
			srcs/parsing/split_2.c \
			srcs/parsing/split_3.c \
			srcs/parsing/split_cmds.c 

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
