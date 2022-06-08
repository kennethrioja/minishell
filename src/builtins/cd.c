/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:05:42 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/02 21:00:55 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_ad *ad)
{
//	DIR	*dir;
	char	buf[PATH_MAX];

	add_env(ad, "OLDPWD", getcwd(buf, PATH_MAX));
	if (!ad->pa->args[1])
	{
		chdir(get_env(ad, get_i_env(ad, "HOME"))->value);
	}
	else if (chdir(ad->pa->args[1]))
	{
		perror("cd");
//		chdir(ad->line + 3);
//		closedir(dir);
	}
	add_env(ad, "PWD", getcwd(buf, PATH_MAX));
//	dir = opendir(ad->pa->args[1]);
//	if (dir)
//	{
//		chdir(ad->pa->args[1]);
//		closedir(dir);
//	}
//	else
//		perror("cd");
}
