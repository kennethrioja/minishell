/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:28:08 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/09 15:28:10 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_ad *ad)
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
}
