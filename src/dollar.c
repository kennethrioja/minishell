/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:48:22 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/13 09:48:26 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_dollar(t_ad *ad)
{
	int	i;

	while (ad->pa)
	{
		i = -1;
		while (++i < (int)ft_arrlen(ad->pa->args))
		{
			if (ad->pa->args[i][0] == '$')
			{
				if (get_i_env(ad, ad->pa->args[i] + 1) != -1)
				{
					ad->pa->args[i] = get_env(ad, get_i_env(ad, ad->pa->args[i] + 1))->value;
				}
			}
		}
		ad->pa = ad->pa->next;
	}
	ad->pa = ad->pa_head;
}
