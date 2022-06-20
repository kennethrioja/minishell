/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:00:43 by krioja            #+#    #+#             */
/*   Updated: 2022/06/20 10:49:31 by krioja           ###   ########.fr       */
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

static void	exec_one_gr(t_ad *ad)
{
	int	pid;
	int	outfile;

	pid = fork();
	if (pid == -1)
		my_exit(ad, write(2, "Error: fork\n", 12));
	if (pid == 0)
	{
		outfile = open(ad->pa->redir->file, O_RDWR | O_CREAT, 0644);
		if (outfile == -1)
			my_exit(ad, write(2, "Error: open\n", 12));
		dup2(outfile, STDOUT_FILENO);
	}
}

static void	do_redir(t_ad *ad)
{
	redir_lst_fst_or_lst(&ad->pa->redir, 0);
	while (ad->pa->redir)
	{
		if (!ft_strncmp(ad->pa->redir->op, ">", 1))
			exec_one_gr(ad);
		/*
		if (ad->pa->redir->op == '<')
			exec_one_sm(ad);
		if (!ft_strncmp(ad->pa->redir->op, ">>", 2)
			exec_two_gr(ad);
		if (!ft_strncmp(ad->pa->redir->op, "<<", 2)
			exec_one_sm(ad);
		*/
		if (ad->pa->redir->next)
			ad->pa->redir = ad->pa->redir->next;
		else
			break ;
	}
	execve(ad->pa->path, ad->pa->args, NULL);
}

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

static int	add_prefix(t_ad *ad, const char *s, int n)
{
	char	**path;
	int		i;

	i = -1;
	env_lst_fst_or_lst(&ad->env, 0);
	while (ft_strncmp(ad->env->key, "PATH", 4))
		ad->env = ad->env->next;
	path = ft_split(ad->env->value, ':');
	ad->pa->path = ft_strjoin(path[n], "/");
	ad->pa->path = ft_strjoin(ad->pa->path, s);
	while (path[++i])
		free(path[i]);
	free(path);
	if (ad->pa->path == NULL)
		return (0);
	return (n + 1);
}

static void	get_path(t_ad *ad)
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
			if (n == 0)
				my_exit(ad, write(2, "adsh: command not found: ", 25)
					+ write(2, ad->pa->args[0], ft_strlen(ad->pa->args[0]))
					+ write(2, "\n", 1));
		}
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
	do_redir(ad);
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
