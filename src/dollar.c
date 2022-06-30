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

// TODO norminette (wannacry isn't only a ransomware)
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
				{
					if (ad->pa->args[i][j] == '$')
					{
						if (ad->pa->args[i][j + 1] == '?')
						{
							ad->pa->args[i] = ft_strsubreplace(ad->pa->args[i], "$?", ft_itoa(g_status_exit));
						}
						if (get_i_env(ad, ad->pa->args[i] + j + 1) != -1)
						{
							ad->pa->args[i] = ft_strsubreplace(ad->pa->args[i], ft_strjoin("$", get_env(ad, get_i_env(ad, ad->pa->args[i] + j + 1))->key), get_env(ad, get_i_env(ad, ad->pa->args[i] + j + 1))->value);
						}
					}
				}
			}
			else
				ad->pa->args[i] = ft_strtrim_f(ad->pa->args[i], "'");
		}
		ad->pa = ad->pa->next;
	}
	ad->pa = ad->pa_head;
}
