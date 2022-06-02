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
//	DIR	*dir;

	//TODO gerer le oldpwd et pwd
	if (!ft_strcmp(ad->line, "cd"))
	{
		chdir(get_env(ad, get_i_env(ad, "HOME"))->value);
//		get_env(ad, get_i_env(ad, "PWD"))->value = getenv("PWD");
//		get_env(ad, get_i_env(ad, "OLDPWD"))->value = getenv("OLDPWD");
		return ;
	}
//	dir = opendir(ad->line + 3);
	if (chdir(ad->line + 3))
	{
		perror("cd");
//		chdir(ad->line + 3);
//		closedir(dir);
	}
	get_env(ad, get_i_env(ad, "PWD"))->value = getenv("PWD");
	get_env(ad, get_i_env(ad, "OLDPWD"))->value = getenv("OLDPWD");
	// dir = opendir(ad->pa->args[1]);
	// if (dir)
	// {
	// 	chdir(ad->pa->args[1]);
	// 	closedir(dir);
	// }
	// else
	// 	ft_printf("cd: no such file or directory: %s\n", ad->line + 3);
}
