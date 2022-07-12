/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_check_execve.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:03:18 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/28 13:29:21 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_env2d(t_node *env)
{
	char	**env2d;
	int		size;
	int		i;
	char	*tmp;

	size = count_t_node(env);
	env2d = ft_calloc(sizeof(char **), size + 1);
	i = -1;
	while (++i < size)
	{
		tmp = ft_strjoin(env->key, "=");
		env2d[i] = ft_strjoin(tmp, env->value);
		free(tmp);
	}
	return (env2d);
}

static int	create_cmd(char **path, char **cmd)
{
	char	*npath;
	int		i;
	int		arr_i;

	arr_i = -1;
	while (++arr_i < (int)ft_arrlen(path))
	{
		i = ft_strlen(path[arr_i]);
		if (path[arr_i][i - 1] != '/' && *cmd[0] != '/')
		{
			npath = ft_strjoin(path[arr_i], "/");
			*cmd = ft_strjoin_f(npath, *cmd, 3);
			if (access(*cmd, X_OK) == 0)
				return (1);
		}
		if (access(*cmd, X_OK) == 0)
			return (1);
	}
	return (0);
}

int	ms_exec_check_execve(t_ad *ad)
{
	char	**path;
	int		is_cmd;

	if (access(ad->pa->cmd, X_OK) == 0)
	{
		ms_exec_redir(ad);
		execve(ad->pa->cmd, ad->pa->args, get_env2d(ad->env));
	}
	else if (get_i_env(ad, "PATH") == -1)
		return (1);
	else
	{
		path = ft_split(get_env(ad, get_i_env(ad, "PATH"))->value, ':');
		is_cmd = create_cmd(path, &ad->pa->cmd);
		free_tab(path);
		if (is_cmd == 0)
			return (1);
		ms_exec_redir(ad);
		execve(ad->pa->cmd, ad->pa->args, get_env2d(ad->env));
	}
	return (0);
}
