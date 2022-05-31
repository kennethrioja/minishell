/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:00:41 by krioja            #+#    #+#             */
/*   Updated: 2022/05/31 20:17:54 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_ad *ad)
{
	while (ad->env && ad->env->next)
	{
		free(ad->env->key);
		free(ad->env->value);
		ad->env = ad->env->next;
		free(ad->env->prev);
	}
	free(ad->env->key);
	free(ad->env->value);
	free(ad->env);
	free(ad->line);
}
