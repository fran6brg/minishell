/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:34:25 by fberger           #+#    #+#             */
/*   Updated: 2020/01/26 01:14:53 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void			put_nl_and_prompt(int signum)
{
	(void)signum;
	ft_putchar('\n');
	put_prompt();
}

/*
** SIGINT ctrl c
** SIGQUIT ctrl backslash
** SIGTSTP ctrl z
*/

void			listen_sig(void)
{
	signal(SIGINT, put_nl_and_prompt);
	signal(SIGQUIT, put_nl_and_prompt); // todo : quit without displaying new prompt (right behaviour)
	signal(SIGTSTP, put_nl_and_prompt);
}