/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:34:25 by fberger           #+#    #+#             */
/*   Updated: 2020/02/06 12:25:33 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	put_nl_and_prompt(int signum)
{
	(void)signum;
	ft_putchar('\n');
	put_prompt();
}

void	put_nothing(int signum)
{
	(void)signum;
}

/*
** listen_sig()
**
** SIGINT ctrl c
** SIGQUIT ctrl backslash
** SIGTSTP ctrl z
*/

void	listen_sig(void)
{
	signal(SIGINT, put_nl_and_prompt);
	signal(SIGQUIT, put_nothing);
	signal(SIGTSTP, put_nl_and_prompt);
}
