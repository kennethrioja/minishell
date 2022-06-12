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

int	count_node(t_node *node)
{
	t_node	*tmp;
	int		i;

	tmp = node;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**get_env2d(t_node *env)
{
	char	**env2d;
	int		size;
	int		i;
	char	*tmp;

	size = count_node(env);
	env2d = ft_calloc(sizeof(char **), size);
	i = -1;
	while (++i < size)
	{
		tmp = ft_strjoin(env->key, "=");
		env2d[i] = ft_strjoin(tmp, env->value);
		free(tmp);
	}
	return (env2d);
}

void	get_path_bin(t_ad *ad, char ***path, int size)
{
	char	*dir;

	dir = ft_strjoin((*path)[size], "/");
	**path = ft_strjoin(dir, ad->pa->args[0]);
}

char	*create_cmd(char *path, char *cmd)
{
	char	*ncmd;
	char	*npath;
	int		i;

	i = ft_strlen(path);
	if (path[i - 1] != '/')
	{
		npath = ft_strjoin(path, "/");
		ncmd = ft_strjoin(npath, cmd);
		free(npath);
		return (ncmd);
	}
	return (cmd);
}

int	check_path(t_ad *ad)
{
	char	**path;
	char	*cmd;
	int		size;
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (access(ad->pa->cmd, X_OK) == 0)
		{
			execve(".", ad->pa->args, get_env2d(ad->env));
		}
		path = ft_split(get_env(ad, get_i_env(ad, "PATH"))->value, ':');
		size = ft_arrlen(path);
		while (size-- > 0)
		{
			cmd = create_cmd(path[size], ad->pa->cmd);
			if (access(cmd, X_OK) == 0)
				execve(cmd, ad->pa->args, get_env2d(ad->env));
		}
		size = ft_arrlen(path);
		while (size-- > 0)
			free(path[size]);
		free(cmd);
		free(path);
		custom_err(ad, 0, "Command not found");
		exit(EXIT_FAILURE);
	}
	waitpid(child_pid, NULL, 0);
	return (1);
}
