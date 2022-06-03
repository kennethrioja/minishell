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
		size = get_i_env(ad, ad->line + 6);
		if (size == -1)
			return ;
		tmp = get_env(ad, size);
		delete_env(&ad->env, tmp);
	}
}

void	delete_env(t_node **head_ref, t_node *del)
{
	if (*head_ref == NULL || del == NULL)
		return ;
	if (*head_ref == del)
		*head_ref = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
	free(del->key);
	free(del->value);
	free(del);
}
