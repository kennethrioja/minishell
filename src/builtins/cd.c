/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:05:42 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/24 09:18:48 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_ad *ad)
{
	DIR	*dir;

	dir = opendir(ad->line + 3);
	if (dir)
	{
		chdir(ad->line + 3);
		closedir(dir);
	}
	else
		ft_printf("cd: no such file or directory: %s\n", ad->line + 3);
	// dir = opendir(ad->pa->args[1]);
	// if (dir)
	// {
	// 	chdir(ad->pa->args[1]);
	// 	closedir(dir);
	// }
	// else
	// 	ft_printf("cd: no such file or directory: %s\n", ad->line + 3);
}
