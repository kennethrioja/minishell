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

static int	ft_isunset(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
			|| str[i] == '_')
			continue ;
		return (0);
	}
	return (1);
}

int	ft_unset(t_ad *ad)
{
	t_node	*tmp;
	int		size;
	int		i;
	int		status;

	i = 0;
	status = SUCCESS;
	while (ad->pa->args[++i])
	{
		if (ft_isunset(ad->pa->args[i]))
		{
			size = get_i_env(ad, ad->pa->args[i]);
			if (size == -1)
				continue ;
			tmp = get_env(ad, size);
			delete_t_node(&ad->env, tmp);
		}
		else
		{
			status = GENERAL_ERR;
			custom_err(ad, i, VALID_IDENTIFIER_MSG);
		}
	}
	g_status_exit = status;
	return (0);
}

void	delete_t_node(t_node **head_ref, t_node *del)
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
