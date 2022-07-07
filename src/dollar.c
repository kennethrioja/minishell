/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:48:22 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/28 11:17:29 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*edit_status_exit(t_ad *ad, int i)
{
	char	*tmp;
	char	*tmp2;
	char	*ret;

	tmp = ad->pa->args[i];
	tmp2 = ft_itoa(g_status_exit);
	ret = ft_strsubreplace(ad->pa->args[i], "$?", tmp2);
	free(tmp);
	free(tmp2);
	return (ret);
}

static void	check_after_dollar(t_ad *ad, int i, int j)
{
	char	*env;
	char	*tmp;
	char	*tmp2;

	if (ad->pa->args[i][j] == '$')
	{
		if (ad->pa->args[i][j + 1] == '?')
		{
			ad->pa->args[i] = edit_status_exit(ad, i);
		}
		env = ft_substr(ad->pa->args[i], j + 1,
				ft_strlen_c(ad->pa->args[i] + j + 1, ' '));
		if (get_i_env(ad, env) != -1)
		{
			tmp = ad->pa->args[i];
			tmp2 = ft_strjoin("$", get_env(ad, get_i_env(ad, env))->key);
			ad->pa->args[i] = ft_strsubreplace(ad->pa->args[i], tmp2,
					get_env(ad, get_i_env(ad, env))->value);
			free(tmp);
			free(tmp2);
		}
		free(env);
	}
}

void	check_dollar(t_ad *ad)
{
	int		i;
	int		j;

	pa_lst_fst_or_lst(&ad->pa, 0);
	if (!ad->pa)
		return ;
	while (ad->pa)
	{
		i = -1;
		while (++i < (int)ft_arrlen(ad->pa->args))
		{
			if (ad->pa->args[i][0] != '\'')
			{
				j = -1;
				while (ad->pa->args[i][++j])
					check_after_dollar(ad, i, j);
			}
			else
				ad->pa->args[i] = ft_strtrim_f(ad->pa->args[i], "'");
		}
		ad->pa = ad->pa->next;
	}
	ad->pa = ad->pa_head;
}
