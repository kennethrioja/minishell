/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:03:18 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/04 18:59:15 by tpinto-m         ###   ########.fr       */
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

void	check_path(t_ad *ad)
{
	char	**path;
	char	**exec;
	int		size;
	int		size2;
	char	*dir;
	char	*check;
	int		err;
	char	**env;
	int		i;
	// pid_t	child_pid;

	// child_pid = fork();
	// if (child_pid != 0)
	// {
	// 	return ;
	// }
	// else
	// {
		path = ft_split(get_env(ad, get_i_env(ad, "PATH"))->value, ':');
		size = ft_arrlen(path);
		env = get_env2d(ad->env);
		while (size--)
		{
			dir = ft_strjoin(path[size], "/");
			exec = ft_split(ad->line, ' ');
			// check exec
			i = 0;
			while (exec[++i])
			{
				if (exec[i][0] != '-')
				{
					free(exec[i]);
					exec[i] = NULL;
				}
			}
			check = ft_strjoin(dir, exec[0]);
			free(dir);
			if (!access(check, F_OK))
			{
				size2 = ft_arrlen(exec);
				err = execve(check, exec, env);
				while (size2--)
					free(exec[size2]);
				free(exec);
				if (err)
					perror("execve");
			}
			free(path[size]);
			free(check);
		}
		free(path);
		// exit(0);
	// }
}
