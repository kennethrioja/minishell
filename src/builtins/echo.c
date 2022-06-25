/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:00:42 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/31 23:40:23 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_ad *ad)
{
	int	n_option;
	int	i;
	int	arrlen;

	n_option = 0;
	if (ad->pa->args[1])
		if (!ft_strcmp(ad->pa->args[1], "-n"))
			n_option = 1;
	i = 1 + n_option;
	arrlen = (int)ft_arrlen(ad->pa->args);
	while (i < arrlen)
	{
		ft_printf("%s", ad->pa->args[i]);
		if (i < arrlen - 1)
			ft_printf(" ");
		i++;
	}
	if (!n_option)
		ft_printf("\n");
	g_status_exit = SUCCESS;
}
