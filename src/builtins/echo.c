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
	int	size;
	// int	i;

	n_option = 0;
	if (!ft_strncmp(ad->line, "echo -n", 7))
		n_option = 1;
	size = ft_strlen(ad->line);
	if (n_option)
	{
		if (size > 7 && ad->line[8] == '$')
		{
			if (getenv(ad->line + 9))
				ft_printf("%s", getenv(ad->line + 9));
		}
		else
			ft_printf("%s", ad->line + 8);
	}
	else
	{
		if (size > 6 && ad->line[5] == '$')
		{
			if (getenv(ad->line + 6))
				ft_printf("%s", getenv(ad->line + 6));
		}
		else
			ft_printf("%s", ad->line + 5);
		ft_printf("\n");
	}
//	 if (!ft_strcmp(ad->pa->args[1], "-n"))
//	 	n_option = 1;
//	 i = 1 + n_option;
//	if (ad->pa->args[i][0] == '$')
//		ft_printf("%s\n", getenv(ad->pa->args[i]));
//	else
//		while (ad->pa->args[i])
//	 		ft_printf("%s", ad->pa->args[i]);
//	 if (!n_option)
//	 	ft_printf("\n");
}
