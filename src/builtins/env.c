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
			ft_printf("%s\n", ad->env[i]);
			i++;
		}
	}
	else
	{
		// wip
		// env TEST=hello
		// TEST=hello=hello
		ft_set_env(ad, ad->line + 4, ad->line + ft_strlen_c(ad->line, '=') + 1, 1);
	}
}

void	init_env(t_ad *ad, char	**env)
{
	int	i;
	int	j;

	i = ft_arrlen(env);
	ad->env = ft_calloc(i + 1, sizeof(ad->env));
	j = 0;
	while (j < i)
	{
		ad->env[j] = ft_strdup(env[j]);
		j++;
	}
	ad->env[j] = NULL;
}

void	ft_set_env(t_ad *ad, char *rule, char *str, int overwrite)
{
	int		i;
	int		j;
	char	*ruleeq;
	char	**tmp;

	j = -1;
	while (ad->env[++j])
	{
		if (!ft_strncmp(ad->env[j], rule, ft_strlen(rule)))
		{
			if (overwrite)
			{
				free(ad->env[j]);
				ruleeq = ft_strjoin(rule, "=");
				ad->env[j] = ft_strjoin(ruleeq, str);
			}
		}
		else
		{
			i = ft_arrlen(ad->env) + 1;
			tmp = ft_calloc(i + 1, sizeof(ad->env));
			j = 0;
			while (j < i - 1)
			{
				tmp[j] = ft_strdup(ad->env[j]);
				j++;
			}
			ruleeq = ft_strjoin(rule, "=");
			ad->env[j] = ft_strjoin(ruleeq, str);
			ad->env[j + 1] = NULL;
		}
	}
}
