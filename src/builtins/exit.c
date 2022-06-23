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

void	ft_exit(t_ad *ad)
{
	int	i;

	ft_printf("exit\n");
	if (ad->pa->args[2])
	{
		custom_err(ad, 0, ARGS_MSG);
		exit(255);
	}
	i = -1;
	while (ad->pa->args[1][++i])
	{
		if (!ft_isdigit(ad->pa->args[1][++i]))
		{
			custom_err(ad, 1, EXIT_MSG);
			exit(255);
		}
	}
	free_all(ad);
	exit(ft_atoi(ad->pa->args[1]));
}
