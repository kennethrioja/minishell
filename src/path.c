/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:03:18 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/06 12:11:53 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env2d(t_node *env)
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

//TODO clean
void	get_path_bin(t_ad *ad, char ***path, int size)
{
	char	*dir;

	dir = ft_strjoin((*path)[size], "/");
	**path = ft_strjoin(dir, ad->pa->args[0]);
}

char	*create_cmd(char **path, char *cmd)
{
	char	*ncmd;
	char	*npath;
	int		i;
	int		arr_i;

	arr_i = ft_arrlen(path);
	while (arr_i-- > 0)
	{
		i = ft_strlen(path[arr_i]);
		if (path[arr_i][i - 1] != '/')
		{
			npath = ft_strjoin(path[arr_i], "/");
			ncmd = ft_strjoin(npath, cmd);
			free(npath);
			if (access(ncmd, X_OK) == 0)
				return (ncmd);
		}
		if (access(cmd, X_OK) == 0)
			return (ncmd);
	}
	return (NULL);
}

void	abs_path(t_ad *ad)
{
	pid_t	child_pid;

	if (access(ad->pa->cmd, X_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			execve(ad->pa->cmd, ad->pa->args, get_env2d(ad->env));
			waitpid(child_pid, &g_status_exit, 0);
			g_status_exit = WIFEXITED(g_status_exit);
		}
	}
}

int	check_path(t_ad *ad)
{
	char	**path;
	char	*cmd;
	pid_t	child_pid;


	if (access(ad->pa->cmd, X_OK) == 0)
	{
		abs_path(ad);
		return (0);
	}
	else if (get_i_env(ad, "PATH") == -1)
		return (1);
	else
	{
		path = ft_split(get_env(ad, get_i_env(ad, "PATH"))->value, ':');
		cmd = create_cmd(path, ad->pa->cmd);
		if (!cmd)
			return (1);
		child_pid = fork();
		if (child_pid == 0)
		{
			execve(cmd, ad->pa->args, get_env2d(ad->env));
			waitpid(child_pid, &g_status_exit, 0);
			g_status_exit = WIFEXITED(g_status_exit);
		}
		return (0);
	}
	return (1);
}
