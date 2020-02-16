# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fberger <fberger@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/07 17:41:37 by fberger           #+#    #+#              #
#    Updated: 2020/02/07 10:14:57 by fberger          ###   ########.fr        #
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
			srcs/builtins/env_utils_1.c \
			srcs/builtins/env_utils_2.c \
			srcs/builtins/pwd.c \
			srcs/builtins/exit.c \
			srcs/exec/single_execv.c \
			srcs/exec/path.c \
			srcs/exec/exec_utils.c \
			srcs/pipeline/pipeline.c \
			srcs/utils/args.c \
			srcs/utils/fd.c \
			srcs/utils/free.c \
			srcs/utils/helpers.c \
			srcs/utils/signal.c \
			srcs/parsing/errors.c \
			srcs/parsing/split_cmd_1.c \
			srcs/parsing/split_cmd_2.c \
			srcs/parsing/split_cmd_3.c \
			srcs/parsing/split_cmds_1.c \
			srcs/parsing/split_cmds_2.c 

OBJS 	= ${SRCS:.c=.o}

LIB 	= -L. libft/libft.a

HEADER 	= -I ./includes/

all: $(NAME)

.c.o:
	@gcc $(FLAGS) $(HEADER) -c $< -o $@

$(NAME): $(OBJS)
	@gcc $(OBJS) -o $(NAME) $(LIB)

clean:
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
