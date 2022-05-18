/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:11:14 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/18 10:51:18 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_line(t_ad *ad)
{
	if (ad->line)
	{
		free(ad->line);
		ad->line = NULL;
	}
	ad->line = readline("A&D Shell>");
	if (ad->line)
		add_history(ad->line);
	if (!ad->line)
		return (0);
	return (1);
}
