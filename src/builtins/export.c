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

static void	sort_export(t_ad *ad, int count);
static void	show_export(t_ad *ad);
static void	add_export(t_ad *ad, int i);

void	ft_export(t_ad *ad)
{
	int	i;
	int	checker;
	int	status;

	status = SUCCESS;
	if (!ad->pa->args[1])
		show_export(ad);
	else
	{
		i = 0;
		while (ad->pa->args[++i])
		{
			checker = ft_isexport(ad->pa->args[i]);
			if (checker)
				add_export(ad, i);
			else
			{
				status = GENERAL_ERR;
				custom_err(ad, i, VALID_IDENTIFIER_MSG);
			}
		}
	}
	ad->status_exit = status;
}

int	ft_isexport(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
			|| str[i] == '=' || str[i] == '_')
			return (1);
	}
	return (0);
}

static void	show_export(t_ad *ad)
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

static void	add_export(t_ad *ad, int i)
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

static void	sort_export(t_ad *ad, int count)
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
