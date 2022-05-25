/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:32:31 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/25 15:32:36 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_ad *ad)
{
	int	i;

	i = 0;
	if (!ft_strcmp(ad->line, "export"))
	{
		while (ad->env[i])
		{
			ft_printf("declare -x %s=\"%s\"\n", ad->env[i][0], ad->env[i][1]);
			i++;
		}
	}
	else
	{
//		ft_set_env(ad, );
		ft_printf("export: %s: No such file or directory\n", ad->line + 4);
	}
}

//void	ft_set_env(t_ad *ad, char *rule, char *str, int overwrite)
//{
//	int		i;
//	int		j;
//	char	*ruleeq;
//	char	**tmp;
//
//	j = -1;
//	while (ad->env[++j])
//	{
//		if (!ft_strncmp(ad->env[j], rule, ft_strlen(rule)))
//		{
//			if (overwrite)
//			{
//				free(ad->env[j]);
//				ruleeq = ft_strjoin(rule, "=");
//				ad->env[j] = ft_strjoin(ruleeq, str);
//			}
//		}
//		else
//		{
//			i = ft_arrlen(ad->env) + 1;
//			tmp = ft_calloc(i + 1, sizeof(ad->env));
//			j = 0;
//			while (j < i - 1)
//			{
//				tmp[j] = ft_strdup(ad->env[j]);
//				j++;
//			}
//			ruleeq = ft_strjoin(rule, "=");
//			ad->env[j] = ft_strjoin(ruleeq, str);
//			ad->env[j + 1] = NULL;
//		}
//	}
//}
