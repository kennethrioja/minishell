/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:20:43 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/24 14:13:40 by tpinto-m         ###   ########.fr       */
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

	i = ft_arrlen(env);
	ad->env = ft_calloc(i + 1, sizeof(ad->env));
	j = 0;
	while (j < i)
	{
		ad->env[j] = ft_calloc(2, sizeof(ad->env[j]));
		ad->env[j][0] = ft_substr(env[j], 0, ft_strlen_c(env[j], '='));
		ad->env[j][1] = ft_strdup(env[j] + 1 + ft_strlen_c(env[j], '='));
		j++;
	}
}
