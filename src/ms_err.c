/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:04:07 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/07/07 15:04:10 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	custom_err(t_ad *ad, int arg, char *str)
{
	write(2, SHELL_NAME, ft_strlen(SHELL_NAME));
	if (arg != 0)
	{
		write(2, ": ", 2);
		write(2, ad->pa->cmd, ft_strlen(ad->pa->cmd));
	}
	write(2, ": ", 2);
	write(2, ad->pa->args[arg], ft_strlen(ad->pa->args[arg]));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void	custom_err_exit(t_ad *ad, int arg, char *str, int ret)
{
	write(2, SHELL_NAME, ft_strlen(SHELL_NAME));
	if (arg != 0)
	{
		write(2, ": ", 2);
		write(2, ad->pa->cmd, ft_strlen(ad->pa->cmd));
	}
	write(2, ": ", 2);
	write(2, ad->pa->args[arg], ft_strlen(ad->pa->args[arg]));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(ret);
}

int	custom_err_ret(char *str, int status, int ret)
{
	g_status_exit = status;
	write(2, str, ft_strlen(str));
	return (ret);
}

void	my_exit(t_ad *ad, int flag)
{
	free_all(ad);
	exit(flag);
}
