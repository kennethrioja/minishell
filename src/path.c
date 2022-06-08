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

void	get_path_bin(t_ad *ad, char ***path, int size, char ***av)
{
	char	**argv;
	char	*dir;
	int		i;

	dir = ft_strjoin((*path)[size], "/");
	argv = ft_split(ad->line, ' ');
	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] != '-')
		{
			free(argv[i]);
			argv[i] = NULL;
		}
	}
	*av = argv;
	**path = ft_strjoin(dir, argv[0]);
}

void	check_path(t_ad *ad)
{
	char	**path;
	char	**av;
	int		size;
	int		size2;
	int		err;

	path = ft_split(get_env(ad, get_i_env(ad, "PATH"))->value, ':');
	size = ft_arrlen(path);
	while (size--)
	{
		get_path_bin(ad, &path, size, &av);
		if (!access(*path, F_OK))
		{
			size2 = ft_arrlen(av);
			err = execve(*path, av, get_env2d(ad->env));
			while (size2--)
				free(av[size2]);
			free(av);
			if (err)
				perror("execve");
		}
	}
	free(path[size]);
	free(path);
}
