/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:20:43 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/31 20:20:31 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_ad *ad)
{
	if (ad->pa->args[1])
	{
		if (access(ad->pa->args[1], X_OK))
		{
			ad->status_exit = NOT_FOUND_ERR;
			custom_err(ad, 1, "No such file or directory");
		}
		else
		{
			ad->status_exit = PERMISSION_ERR;
			custom_err(ad, 1, "Permission denied");
		}
	}
	else
	{
		ad->status_exit = SUCCESS;
		print_node(ad->env, 'c');
	}
}

int	get_i_env(t_ad *ad, char *key)
{
	t_node	*tmp;
	int		i;

	tmp = ad->env;
	i = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (-1);
}

t_node	*get_env(t_ad *ad, int i)
{
	t_node	*tmp;

	tmp = ad->env;
	while (i--)
		tmp = tmp->next;
	return (tmp);
}

void	init(t_ad *ad, char	**env)
{
	size_t	i;
	size_t	j;
	char	*key;
	char	*value;

	i = ft_arrlen(env);
	ad->env = NULL;
	j = 0;
	while (j < i)
	{
		key = ft_substr(env[j], 0, ft_strlen_c(env[j], '='));
		value = ft_strdup(env[j] + 1 + ft_strlen_c(env[j], '='));
		append_t_node(&ad->env, key, value);
		j++;
	}
	ad->redir = NULL;
	ad->pa = NULL;
	ad->status_exit = 0;
}

void	add_env(t_ad *ad, int arg, char *name, char *value)
{
	t_node	*tmp;
	int		i;

	if (!name)
		name = ft_substr(ad->pa->args[arg], 0,
				ft_strlen_c(ad->pa->args[arg], '='));
	if (!value)
		value = ft_strdup(ad->pa->args[arg] + ft_strlen_c(ad->pa->args[arg],
					'=') + 1);
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
