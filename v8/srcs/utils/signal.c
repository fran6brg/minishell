/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:34:25 by fberger           #+#    #+#             */
/*   Updated: 2020/02/07 14:33:23 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		*shell_is_running_cmd(void)
{
	static int i;

	return (&i);
}

/*
** https://stackoverflow.com/questions/35519157
** https://stackoverflow.com/questions/2386923
*/

void	put_nl_and_prompt(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr("\b\b  \n");
		if (!*shell_is_running_cmd())
			put_prompt();
	}
	else if (signum == SIGQUIT)
	{
		ft_putstr("\033[1K");
		ft_putstr("\r");
		if (!*shell_is_running_cmd())
			put_prompt();
	}
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
	signal(SIGQUIT, put_nl_and_prompt);
	signal(SIGTSTP, put_nl_and_prompt);
}
