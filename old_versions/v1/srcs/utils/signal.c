/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <fberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:34:25 by fberger           #+#    #+#             */
/*   Updated: 2020/01/15 17:42:17 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void			nl_prompt(int signum)
{
	(void)signum;
	ft_putchar('\n');
	put_prompt();
}

// static void			nothing(int signum)
// {
// 	(void)signum;;
// }

void			sigint_handler(void)
{
	signal(SIGINT, nl_prompt); // ctrl c
	signal(SIGQUIT, nl_prompt); // ctrl backslash
	signal(SIGTSTP, nl_prompt); // ctrl z
}