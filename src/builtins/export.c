/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:32:31 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/31 23:35:18 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_ad *ad)
{
	t_node	*tmp;
	char	*key;
	char	*value;

	tmp = ad->env;
	if (!ft_strcmp(ad->line, "export"))
	{
		while (tmp)
		{
			ft_printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
	else
	{
		key = ft_substr(ad->line, 7, ft_strlen_c(ad->line, '=') - 7);
		value = ft_strdup(ad->line + ft_strlen_c(ad->line, '=') + 1);
		while (tmp)
		{
			if (check_export(tmp->key, key))
			{
				free(tmp->value);
				free(key);
				tmp->value = value;
				return ;
			}
			tmp = tmp->next;
		}
		append_env(&ad->env, key, value);
	}
}

int	check_export(char *env, char *key)
{
	if (!ft_strcmp(env, key))
		return (1);
	return (0);
}

void	append_env(t_node **head_ref, char *key, char *value)
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
