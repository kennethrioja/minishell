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

int	count_t_node(t_ad *ad)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = ad->env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	append_t_node(t_node **head_ref, char *key, char *value)
{
	t_node	*new_node;
	t_node	*last;

	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	if (*head_ref == NULL)
	{
		new_node->prev = NULL;
		*head_ref = new_node;
		return ;
	}
	last = *head_ref;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
}
