/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:32:31 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/02 20:53:13 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_ad *ad)
{
	// t_node	*dup;


	if (!ft_strcmp(ad->line, "export"))
	{
		sort_export(ad, count_export(ad));
	}
	else
	{
		add_env(ad, NULL, NULL);
	}
}

void	add_env(t_ad *ad, char *key, char *value)
{
	t_node	*tmp;
	int		i;

	if (!key)
		key = ft_substr(ad->line, 7, ft_strlen_c(ad->line, '=') - 7);
	if (!value)
		value = ft_strdup(ad->line + ft_strlen_c(ad->line, '=') + 1);
	i = get_i_env(ad, key);
	if (i == -1)
		append_env(&ad->env, key, value);
	else
	{
		tmp = get_env(ad, i);
		free(tmp->value);
		tmp->value = ft_strdup(value);
	}
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

int	count_export(t_ad *ad)
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

void	sort_export(t_ad *ad, int count)
{
	t_node	*tmp;
	int		i;
	int		j;
	char	*tmps;

	i = 0;
	while (i++ < count)
	{
		j = 0 + i;
		tmp = ad->env;
		while (j++ < count)
		{
			if (strcmp(tmp->key, tmp->next->key) > 0)
			{
				tmps = tmp->value;
				tmp->value = tmp->next->value;
				tmp->next->value = tmps;
				tmps = tmp->key;
				tmp->key = tmp->next->key;
				tmp->next->key = tmps;
			}
			tmp = tmp->next;
		}
	}
	print_node(tmp, 1);
}
