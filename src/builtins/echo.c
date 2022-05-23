/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:00:42 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/23 16:03:52 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_ad *ad)
{
	int	n_option;
	// int	i;

	n_option = 0;
	if (!ft_strncmp(ad->line, "echo -n", 7))
		n_option = 1;
	if (!n_option)
		ft_printf("%s\n", ad->line + 5);
	else if (n_option)
		ft_printf("%s", ad->line + 8);
	// if (!ft_strcmp(ad->pa->args[1], "-n"))
	// 	n_option = 1;
	// i = 1 + n_option;
	// while (ad->pa->args[i])
	// 	ft_printf("%s", ad->pa->args[i]);
	// if (!n_option)
	// 	ft_printf("\n");
}
