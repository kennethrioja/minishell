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

void	show_export(t_ad *ad)
{
	t_ad	dup;
	t_node	*tmp;

	dup.env = NULL;
	tmp = ad->env;
	while (tmp)
	{
		add_env(&dup, 1, ft_strdup(tmp->key), ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	sort_export(&dup, count_t_node(&dup));
	free_env(&dup);
}

void	ft_export(t_ad *ad)
{
	int	i;

	if (!ad->pa->args[1])
	{
		ad->status_exit = SUCCESS;
		show_export(ad);
	}
	else
	{
		//TODO CHECK IS ALPHA
		i = 0;
		while (ad->pa->args[++i])
		{
			if (ft_strchr(ad->pa->args[i], '='))
			{
				if (ft_strlen(ft_strchr(ad->pa->args[i], '=')) > 1)
					add_env(ad, i, NULL, NULL);
				else
					add_env(ad, i, NULL, ft_strdup(""));
			}
			else
				add_env(ad, i, NULL, ft_strdup("NULL"));
		}
	}
}

void	add_env(t_ad *ad, int arg, char *name, char *value)
{
	t_node	*tmp;
	int		i;

	if (!name)
		name = ft_substr(ad->pa->args[arg], 0, ft_strlen_c(ad->pa->args[arg], '='));
	if (!value)
		value = ft_strdup(ad->pa->args[arg] + ft_strlen_c(ad->pa->args[arg], '=') + 1);
	i = get_i_env(ad, name);
	if (i == -1)
		append_t_node(&ad->env, name, value);
	else
	{
		tmp = get_env(ad, i);
		tmp->value = value;
	}
	ad->status_exit = SUCCESS;
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
