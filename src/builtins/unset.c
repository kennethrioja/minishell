/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:56:41 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/31 22:34:18 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_ad *ad)
{
	t_node	*tmp;
	int		size;

	if (ft_strlen(ad->line) > 6)
	{
		tmp = ad->env;
		while (tmp)
		{
			if (ft_strlen(tmp->key) < ft_strlen(ad->line + 6))
				size = ft_strlen(ad->line + 6);
			else
				size = ft_strlen(tmp->key);
			if (!ft_strncmp(tmp->key, ad->line + 6, size))
			{
				delete_env(&ad->env, tmp);
				break ;
			}
			tmp = tmp->next;
		}
	}
}
