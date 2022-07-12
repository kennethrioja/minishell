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

int	ft_cd(t_ad *ad)
{
	char	buf[PATH_MAX];

	free(get_env(ad, get_i_env(ad, "OLDPWD"))->value);
	add_env(ad, 0, "OLDPWD", ft_strdup(getcwd(buf, PATH_MAX)));
	if (!ad->pa->args[1])
	{
		chdir(get_env(ad, get_i_env(ad, "HOME"))->value);
	}
	else if (chdir(ad->pa->args[1]))
	{
		g_status_exit = GENERAL_ERR;
		if (access(ad->pa->args[1], F_OK))
			custom_err(ad, 1, NOT_FOUND_DIR_MSG);
		else
			custom_err(ad, 1, PERMISSION_MSG);
		return (0);
	}
	free(get_env(ad, get_i_env(ad, "PWD"))->value);
	add_env(ad, 0, "PWD", ft_strdup(getcwd(buf, PATH_MAX)));
	g_status_exit = SUCCESS;
	return (0);
}
