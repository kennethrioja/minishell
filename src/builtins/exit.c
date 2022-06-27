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
	i = ft_arrlen(ad->pa->args);
	if (i > 2)
	{
		custom_err(ad, 0, ARGS_MSG);
		exit(EXIT_ERR);
	}
	if (i == 2)
	{
		i = -1;
		while (ad->pa->args[1][++i])
		{
			if (!ft_isdigit(ad->pa->args[1][i]))
			{
				custom_err(ad, 1, EXIT_MSG);
				exit(EXIT_ERR);
			}
		}
		exit(ft_atoi(ad->pa->args[1]));
	}
	free_all(ad);
	exit(EXIT_SUCCESS);
}
