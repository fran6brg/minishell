/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 04:41:10 by fberger           #+#    #+#             */
/*   Updated: 2020/02/10 17:50:41 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** ft_inc_nb_quote()
*/

void	ft_inc_nb_quote(int *nb, int *i, char *s)
{
	ft_inc_to_closing_quote(i, s);
	*nb += 1;
}

/*
** ft_inc_nb_redirect()
** 	if (j > 0)
**      *nb += 1; // filename
*/

void	ft_inc_nb_redirect(int *nb, int *i, char *s)
{
	int j;

	*nb += 1;
	*i += (s[*i] == '>' && s[*i + 1] == '>') ? 1 : 0;
	*i += 1;
	while (s[*i] && is_separator(s[*i]))
		*i += 1;
	j = 0;
	while (s[*i + j] && !is_separator(s[*i + j]))
		j += 1;
	if (j > 0)
		*nb += 1;
}

/*
** ft_inc_nb_str()
*/

void	ft_inc_nb_str(int *nb, int *i, char *s)
{
	ft_inc_to_end_of_word(i, s);
	*nb += 1;
}

/*
** nb_new_s()
*/

int		nb_new_s(char *s)
{
	int i;
	int nb;

	i = -1;
	nb = 0;
	while (s[++i])
	{
		if (PARSE)
			printf(">> s[%d] = %c | nb = %d\n", i, s[i], nb); // pour debug
		if (is_quote(s[i]))
			ft_inc_nb_quote(&nb, &i, s);
		else if (is_redirect(s[i]))
			ft_inc_nb_redirect(&nb, &i, s);
		else if (s[i] == '|')
			nb++;
		else if (is_separator(s[i]))
			;
		else
			ft_inc_nb_str(&nb, &i, s);
		if (PARSE)
			printf("   s[%d] = %c | nb = %d\n", i, s[i], nb); // pour debug
	}
	return (nb);
}
