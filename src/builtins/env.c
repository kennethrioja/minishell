/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:20:43 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/30 13:31:01 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_ad *ad)
{
	int	i;

	i = 0;
	if (!ft_strcmp(ad->line, "env"))
	{
		while (ad->env[i])
		{
			ft_printf("%s=%s\n", ad->env[i][0], ad->env[i][1]);
			i++;
		}
	}
	else
	{
		ft_printf("env: %s: No such file or directory\n", ad->line + 4);
	}
}

void	init_env(t_ad *ad, char	**env)
{
	size_t	i;
	size_t	j;
	char	*key;
	char	*value;

	i = ft_arrlen(env);
	ad->env_s = NULL;
	j = 0;
	while (j < i)
	{
		key = ft_substr(env[j], 0, ft_strlen_c(env[j], '='));
		value = ft_strdup(env[j] + 1 + ft_strlen_c(env[j], '='));
		append_env(&ad->env_s, key, value);
		// free(key);
		// free(value);
		j++;
	}
}
