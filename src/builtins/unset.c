/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:56:41 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/30 18:56:43 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_ad *ad)
{
	//TODO wip doesn't work
	t_node	*tmp;

	if (ft_strlen(ad->line) > 6)
	{
		tmp = ad->env;
		while (tmp && tmp->next)
		{
//			ft_printf("[%s]\n", ad->line + 6);
			if (!ft_strncmp(tmp->key, ad->line + 6, ft_strlen(ad->line + 6)))
				delete_env(&tmp, tmp);
			tmp = tmp->next;
		}
	}
}
