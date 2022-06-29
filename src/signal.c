/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:51:51 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/18 09:11:16 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
		ft_printf("\r");
		rl_on_new_line();
		rl_redisplay();
	}
	g_status_exit = GENERAL_ERR;
}

void	handle_signal(void)
{
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
}

static void	child_handler(int signum)
{
	if (signum == SIGINT)
		ft_printf("\n");
	if (signum == SIGQUIT)
		ft_printf("Quit: %d\n", SIGQUIT);
}

void	handle_child_signal(void)
{
	signal(SIGQUIT, child_handler);
	signal(SIGINT, child_handler);
}
