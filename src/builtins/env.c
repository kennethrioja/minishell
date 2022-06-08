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
	if (!ft_strcmp(ad->line, "env"))
	{
		print_node(ad->env, 'c');
	}
	else
	{
		perror("env");
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

void	init_env(t_ad *ad, char	**env)
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
		append_env(&ad->env, key, value);
		j++;
	}
}

void	print_node(t_node	*node, int option)
{
	while (node)
	{
		if (option == 1)
			ft_printf("declare -x %s=\"%s\"\n", node->key, node->value);
		else
			ft_printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
}
