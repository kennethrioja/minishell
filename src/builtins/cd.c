/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:05:42 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/31 23:44:01 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_ad *ad)
{
	DIR	*dir;

	if (!ft_strcmp(ad->line, "cd"))
	{
		chdir(getenv("HOME"));
		return ;
	}
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
