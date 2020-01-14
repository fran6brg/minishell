/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 22:18:15 by fberger           #+#    #+#             */
/*   Updated: 2020/01/14 16:11:28 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
** ***************************** includes *************************************
*/

/*
** libft ----------------------------------------------------------------------
*/

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

/*
** GNL ------------------------------------------------------------------------
*/

# include <limits.h>
# include <fcntl.h>

/*
** printf ---------------------------------------------------------------------
*/

# include <string.h>
# include <stdarg.h>

/*
** ***************************** functions ************************************
*/

/*
** libft ----------------------------------------------------------------------
*/

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*
** put
*/

void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
int					ft_putnbr(long long n);
void				ft_putnbr_fd(int n, int fd);
int					ft_putnbr_base(unsigned long long int value, int b, int x);

/*
** mem
*/

void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				*ft_calloc(size_t count, size_t size);

/*
** str
*/

size_t				ft_strlen(const char *s);
char				*ft_strnew(size_t size);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *s1, size_t n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strstr(const char *m, const char *a);
char				*ft_strnstr(const char *m, const char *a, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_free(char *s1, char *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strfulltrim(char const *s1, char const *set);
char				*ft_strtrim_ws(char const *s1);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				**ft_split(char const *s, char c);
char				**ft_split_set(char const *s, char *separators);
char				**ft_split_set_and_quotes(char const *s, char *separators);
int					ft_str_start_with(char *str, char *end);
int					ft_str_end_with(char *str, char *end);
int					ft_letterequci(char c1, char c2);
int					ft_strequci(char *s1, char *s2);
int					ft_next_char_pos(const char *s, char *set);

/*
** nbr
*/

int					ft_nbrlen(long long value, int base);
int					ft_unbrlen(uintmax_t nbr, int base);
char				*ft_intmax_ttoa_base_ws(intmax_t nbr, char *base);
char				*ft_uintmax_ttoa_base(uintmax_t nbr, char *base);
int					ft_min(int a, int b);
int					ft_max(int a, int b);
void				ft_swap_int(int *a, int *b);
int					ft_set_int_in_range(int min, int nb, int max);

/*
** parse
*/

int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_atoi(const char *str);
char				*ft_itoa(int n);

/*
** lst
*/

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));


/*
** GNL ------------------------------------------------------------------------
*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int					get_next_line(const int fd, char **line);

/*
** printf ---------------------------------------------------------------------
*/

#define COL_NRM  "\x1B[0m"
#define COL_RED  "\x1B[31m"
#define COL_GRN  "\x1B[32m"
#define COL_YEL  "\x1B[33m"
#define COL_BLU  "\x1B[34m"
#define COL_MAG  "\x1B[35m"
#define COL_CYN  "\x1B[36m"
#define COL_WHT  "\x1B[37m"

typedef struct						s_options
{
	char							type;
	char							*flags;
	int								fpos;
	int								flen;
	int								neg;
	int								left_justify;
	int								sign;
	int								space;
	int								hashtag;
	int								left_zeros;
	int								point;
	int								width;
	int								width_zero;
	int								precision;
	int								precision_zero;
	int								wildcard;
	int								h;
	int								hh;
	int								l;
	int								ll;
	int								j;
	int								z;
	int								sign_is_print;
	char							*output;
	int								writezero;
	int								ret;
	struct s_options				*next;
}									t_options;

# define NB_ACCEPTED_OPTIONS (13)

typedef struct			s_func
{
	char	option;
	int		(*f)(t_options*, va_list*);
}						t_functions_pointers;

int			ft_printf(const char *f, ...);
int			extract_options(const char *f, t_options **opts, va_list *args);
int			init_option(const char *f, t_options *new, int i, va_list *args);
int			compute_flen(const char *formt, int i);
int			ft_print_char(t_options *opt, va_list *args);
int			ft_print_modulo(t_options *opt, va_list *args);
int			handle_single_percent(const char *f, int i);
int			ft_print_string(t_options *opt, va_list *args);
int			helper_str_pad(t_options *opt, int ln, int aftr);
int			ft_print_integer(t_options *opt, va_list *args);
int			ft_print_base(t_options *opt, va_list *args);
int			get_base(t_options *opt);
int			helper_nb_pad(t_options *opt, int l, int a, long long n);
int			ft_print_floats(t_options *opt, va_list *args);
int			add_nchar_ret(t_options *opt, char c, int n);
int			add_str_ret(t_options *opt, char *str);
int			add_nstr_ret(t_options *opt, char *str, int n);
int			add_nbr_to_output(t_options *option, intmax_t nbr, char *base);
int			add_unbr_to_output(t_options *option, uintmax_t nbr, char *base);
void		ft_print_output(t_options *option);

#endif
