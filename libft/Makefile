# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fberger <fberger@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 17:33:34 by fberger           #+#    #+#              #
#    Updated: 2020/01/10 21:26:14 by fberger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc

CFLAGS=-Wall -Wextra -Werror

NAME=libft.a

SRCS=ft_putchar.c \
	ft_putchar_fd.c \
	ft_putstr.c \
	ft_putstr_fd.c \
	ft_putendl.c \
	ft_putendl_fd.c \
	ft_putnbr.c \
	ft_putnbr_fd.c \
	ft_putnbr_base.c \
	ft_bzero.c \
	ft_memset.c \
	ft_memcpy.c \
	ft_memccpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memalloc.c \
	ft_memdel.c \
	ft_calloc.c \
	ft_strlen.c \
	ft_strnew.c \
	ft_strdup.c \
	ft_strndup.c \
	ft_substr.c \
	ft_strstr.c \
	ft_strnstr.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strcmp.c \
	ft_strncmp.c \
	ft_strequ.c \
	ft_strnequ.c \
	ft_strcpy.c \
	ft_strncpy.c \
	ft_strlcpy.c \
	ft_strcat.c \
	ft_strncat.c \
	ft_strlcat.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_strtrim_ws.c \
	ft_strfulltrim.c \
	ft_strdel.c \
	ft_strclr.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_split.c \
	ft_nbrlen.c \
	ft_unbrlen.c \
	ft_intmax_ttoa_base_ws.c \
	ft_uintmax_ttoa_base.c \
	ft_min.c \
	ft_max.c \
	ft_swap_int.c \
	ft_set_int_in_range.c \
	ft_isalpha.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_atoi.c \
	ft_itoa.c \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_str_end_with.c \
	ft_get_next_line.c \
	ft_format_parse.c \
	ft_printf.c \
	ft_print_cs.c \
	ft_print_di.c \
	ft_print_base.c \
	ft_print_f.c \
	ft_print_nbr_padding.c \
	ft_output_utils.c \
	ft_set_option.c \
	ft_letterequci.c \
	ft_strequci.c


OBJS=${SRCS:.c=.o}

all: $(NAME)

$(NAME):
		$(CC) $(CFLAGS) -c $(SRCS)
		ar rc $(NAME) $(OBJS)
		ranlib $(NAME)

clean:
		@rm -f $(OBJS)

fclean: clean
		@rm -f $(NAME)

re: fclean all
