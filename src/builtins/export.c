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
	t_ad	dup;
	t_node	*tmp;
	int		i;

//	//TODO fix leaks here
	if (!ad->pa->args[1])
	{
		dup.env = NULL;
		tmp = ad->env;
		while (tmp)
		{
			add_env(&dup, 1, tmp->key, tmp->value);
			tmp = tmp->next;
		}
		sort_export(&dup, count_export(&dup));
//		free_env(&dup);
	}
	else
	{
//		key = ft_substr(ad->pa->args[arg], 0, ft_strlen_c(ad->pa->args[arg], '='));
		i = 0;
		while (ad->pa->args[++i])
		{
			printf("%s\n", ft_strchr(ad->pa->args[i], '='));
			if (ft_strchr(ad->pa->args[i], '='))
			{
				if (ft_strlen(ft_strchr(ad->pa->args[i], '=')) > 1)
					add_env(ad, i, NULL, NULL);
				else
					add_env(ad, i, NULL, ft_strdup(""));
			}
			else
				add_env(ad, i, NULL, NULL);
		}
	}
}

void	add_env(t_ad *ad, int arg, char *key, char *value)
{
	t_node	*tmp;
	int		i;

	if (!key)
		key = ft_substr(ad->pa->args[arg], 0, ft_strlen_c(ad->pa->args[arg], '='));
	if (!value)
	{
		if (ft_strchr(ad->pa->args[arg], '='))
			value = ft_strdup(ad->pa->args[arg] + ft_strlen_c(ad->pa->args[arg], '=') + 1);
		else
			value = NULL;
	}
	i = get_i_env(ad, key);
	if (i == -1)
		append_env(&ad->env, key, value);
	else
	{
		tmp = get_env(ad, i);
		tmp->value = value;
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
