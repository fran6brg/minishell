/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:34:25 by fberger           #+#    #+#             */
/*   Updated: 2020/02/08 16:13:04 by fberger          ###   ########.fr       */
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
		if (*shell_is_running_cmd())
		{
			ft_putstr(CLR_LINE);
			ft_putstr(MVCURSOR_BEGL);
		}
		else
		{
			ft_putstr(MVCURSOR_LEFT);
			ft_putstr(MVCURSOR_LEFT);
			ft_putstr(CLR_LINE_RIGHT);
		}		
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
