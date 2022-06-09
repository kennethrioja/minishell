/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:00:43 by krioja            #+#    #+#             */
/*   Updated: 2022/06/09 22:47:31 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*


static int	pipex2(char **argv, char *path2, char **params2, int *fd)
{
	int	outfile;
	int	pid2;

	pid2 = fork();
	if (pid2 == 0)
	{
		outfile = open(argv[4], O_RDWR | O_CREAT, 0644);
		if (outfile == -1)
			return (3);
		dup2(fd[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(outfile);
		execve(path2, params2, NULL);
	}
	return (pid2);
}

int	pipex(char **argv, char **paths, char **params1, char **params2)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == -1)
		return (2);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(paths[0], params1, NULL);
	}
	pid2 = pipex2(argv, paths[1], params2, fd);
	if (pid2 == -1)
		return (4);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
*/

static void	env_lst_fst_or_lst(t_node **env, int flag)
{
	if (flag == 0)
	{
		while (*env)
		{
			if ((*env)->prev == NULL)
				break ;
			*env = (*env)->prev;
		}
	}
	else
	{
		while (*env)
		{
			if ((*env)->next == NULL)
				break ;
			*env = (*env)->next;
		}
	}
}

/*
static char	**add_prefix(char ***params, char **path, char *prefix)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (prefix[1] == 'b')
	{
		*path = malloc(sizeof(char) * (word_length((*params)[0], 0) + 5 + 1));
		while (prefix[++i])
			(*path)[i] = prefix[i];
		while ((*params)[0][++j])
			(*path)[i++] = (*params)[0][j];
		(*path)[i] = '\0';
		return (path);
	}
	*path = malloc(sizeof(char) * (word_length((*params)[0], 0) + 9 + 1));
	while (prefix[++i])
		(*path)[i] = prefix[i];
	while ((*params)[0][++j])
		(*path)[i++] = (*params)[0][j];
	(*path)[i] = '\0';
	return (path);
}

static void	get_path(char ***params, char **path)
{
	path = add_prefix(params, path, "/bin/");
	if (access(*path, F_OK) == -1)
	{
		free(*path);
		path = add_prefix(params, path, "/usr/bin/");
		if (access(*path, F_OK) == -1)
		{
			free(*path);
			perror("Error (path)");
		}
	}
}
*/

/*
static void	add_nth_prefix(t_ad *ad, const char *s, const int n)
{
	while (*s && n)
	{
		if (*s == ':')
			--n;
		*s++;
	}

	ad->pa->path = ft_strjoin(ft_split(ad->env->value, ':')[n], ad->pa->cmd);
}
*/

static int add_prefix(t_ad *ad, const char *s, int n)
{
	char	**path;
	int		i;

	i = -1;
	env_lst_fst_or_lst(&ad->env, 0);
	while (ft_strncmp(ad->env->key, "PATH", 4))
		ad->env = ad->env->next;
//	ft_printf("envkey=|%s|\n", ad->env->key);
	path = ft_split(ad->env->value, ':');
//	ft_printf("path[%d]=|%s|\n", n, path[n]);
	ad->pa->path = ft_strjoin(path[n], s);
//	ft_printf("ad->pa->path=|%s|\n", ad->pa->path);
//	add_nth_prefix(ad, ad->env->value, n)
	while (path[++i])
		free(path[i]);
	free(path);
//	if (!ft_strncmp(ad->pa->path, s, ft_strlen(s)))
	if (ad->pa->path == NULL)
	{
//		ft_printf("PATH IS NULL\n");
		return (0);
	}
	return (n + 1);
}

static void get_path(t_ad *ad)
{
	int	n;

	n = 0;
	pa_lst_fst_or_lst(&ad->pa, 0);
	while (ad->pa)
	{
		while (access(ad->pa->path, F_OK) == -1)
		{
			if (ad->pa->path)
				free(ad->pa->path);
			n = add_prefix(ad, ad->pa->cmd, n);
//			ft_printf("YO N IS %d\n", n);
			if (n == 0)
				my_exit(ad, write(2, "adsh: command not found: ", 25)
						+ write(2, ad->pa->args[0], ft_strlen(ad->pa->args[0]))
						+ write(2, "\n", 1));
		}
		ft_printf("right path for cmd : |%s| is : |%s|\n",ad->pa->args[0], ad->pa->path);
		if (ad->pa->next)
			ad->pa = ad->pa->next;
		else
			break ;
		n = 0;
	}
}

int	ms_pipex(t_ad *ad)
{
	get_path(ad);
//	return (0);

	int	n = 0;
/*
	env_lst_fst_or_lst(&ad->env, 0);
	while (ad->env)
	{
		ft_printf("*ad.env.key=|%s|\n", ad->env->key);
		ft_printf("*ad.env.value=|%s|\n", ad->env->value);
		ad->env = ad->env->next;
	}
*/
	pa_lst_fst_or_lst(&ad->pa, 0);
//	ft_printf("adpacmd=|%s|\n", ad->pa->cmd); //seg fault because ad pa is null
	while (ad->pa)
	{
		ft_printf("--ad.pa.cmd=|%s|\n", ad->pa->cmd);
		ft_printf("ad.pa.path=|%s|\n", ad->pa->path);
		while (ad->pa->args[n])
		{
			ft_printf("ad.pa.args[%d]=|%s|\n", n, ad->pa->args[n]);
			++n;
		}
		redir_lst_fst_or_lst(&ad->pa->redir, 0);
		while (ad->pa->redir)
		{
			ft_printf("ad.pa.redir.op=|%s|\n", ad->pa->redir->op);
			ft_printf("ad.pa.redir.file=|%s|\n", ad->pa->redir->file);
			ad->pa->redir = ad->pa->redir->next;
		}
		if (ad->pa->next)
			ad->pa = ad->pa->next;
		else
			break ;
		n = 0;
	}
	return (0);
}
