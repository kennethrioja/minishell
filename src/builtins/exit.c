/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:22:03 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/23 14:22:14 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void static	exit_no_arg(t_ad *ad)
{
	int	i;

	i = ft_arrlen(ad->pa->args);
	if (i == 1)
		exit(EXIT_SUCCESS);
}

void	ft_exit(t_ad *ad)
{
	int	i;
	int	j;

	ft_printf("exit\n");
	exit_no_arg(ad);
	i = 0;
	while (++i < (int)ft_arrlen(ad->pa->args))
	{
		j = -1;
		while (ad->pa->args[1][++j])
		{
			if (!ft_isdigit(ad->pa->args[1][j]))
			{
				custom_err(ad, 1, EXIT_MSG);
				exit(EXIT_ERR);
			}
		}
	}
	if (i > 2)
	{
		custom_err(ad, 0, ARGS_MSG);
		g_status_exit = GENERAL_ERR;
		return ;
	}
	exit(ft_atoi(ad->pa->args[1]));
}
