/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:00:43 by krioja            #+#    #+#             */
/*   Updated: 2022/06/21 15:22:03 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static int	is_last_redir(t_ad *ad, char *cmp)
{
	t_ad *tmp;
	int	n;

	tmp = ad;
	n = -1;
	while (ad->pa->redir)
	{
		if (!ft_strncmp(ad->pa->redir->op, cmp, ft_strlen(cmp)))
			++n;
		if (ad->pa->redir->next)
			ad->pa->redir = ad->pa->redir->next;
		else
			break;
	}
	ad = tmp;
	if (n)
		return (0);
	return (1);
}

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

static void	redir_two_sm(t_ad *ad)
{
	char *tmp;
	int	fd[2];

	redir_lst_fst_or_lst(&ad->pa->redir, 0);
	while (ad->pa->redir)
	{
		if (!ft_strcmp(ad->pa->redir->op, "<<"))
		{
			if (pipe(fd) == -1)
				my_exit(ad, write(2, "Error: pipe for <<\n", 19));
			while (ft_strcmp(ad->pa->redir->file, tmp))
			{
				tmp = readline("> ");
				if (!ft_strcmp(ad->pa->redir->file, tmp))
					break ;
				write(fd[1], tmp, ft_strlen(tmp));
				write(fd[1], "\n", 1);
				if (tmp)
					free(tmp);
			}
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
		}
		if (ad->pa->redir->next)
			ad->pa->redir = ad->pa->redir->next;
		else
			break;
	}
	close(fd[0]);
	close(fd[1]);
}

static void	redir_one_sm(t_ad *ad)
{
	int	infile;

	redir_lst_fst_or_lst(&ad->pa->redir, 0);
	while (ad->pa->redir)
	{
		if (!ft_strcmp(ad->pa->redir->op, "<"))
		{
			infile = open(ad->pa->redir->file, O_RDWR);
			if (infile == -1)
				my_exit(ad, write(2, "adsh: ", 6)
					+ write(2, ad->pa->redir->file, ft_strlen(ad->pa->redir->file))
					+ write(2, ": No such file or directory\n", 28));
			dup2(infile, STDIN_FILENO);
			close(infile);
		}
		if (ad->pa->redir->next)
			ad->pa->redir = ad->pa->redir->next;
		else
			break;
	}
}

static void	redir_gr(t_ad *ad)
{
	int	outfile;
	
	redir_lst_fst_or_lst(&ad->pa->redir, 0);
	while (ad->pa->redir)
	{
		if (!ft_strncmp(ad->pa->redir->op, ">", 1))
		{
			if (!ft_strcmp(ad->pa->redir->op, ">>"))
				outfile = open(ad->pa->redir->file, O_RDWR | O_APPEND | O_CREAT  , 0644);
			else
				outfile = open(ad->pa->redir->file, O_RDWR | O_CREAT, 0644);
			if (outfile == -1)
				my_exit(ad, write(2, "Error: outfile\n", 15));
			dup2(outfile, STDOUT_FILENO);
			close(outfile);
		}
		if (ad->pa->redir->next)
			ad->pa->redir = ad->pa->redir->next;
		else
			break;
	}
}

static void	exec_redir_multiple(t_ad *ad)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		my_exit(ad, write(2, "Error: fork\n", 12));
	if (pid == 0)
	{
		redir_gr(ad);
		redir_two_sm(ad);
		redir_one_sm(ad);
		execve(ad->pa->path, ad->pa->args, NULL);
	}
	waitpid(pid, NULL, 0);
}

static void	exec_redir_null(t_ad *ad)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		my_exit(ad, write(2, "Error: fork\n", 12));
	if (pid == 0)
		execve(ad->pa->path, ad->pa->args, NULL);
	waitpid(pid, NULL, 0);
}

int	ms_exec(t_ad *ad)
{
	get_path(ad);
	if (!ad->pa->redir)
		exec_redir_null(ad);
	else
		exec_redir_multiple(ad);
//	return (0);

/*
	int	n = 0;
	env_lst_fst_or_lst(&ad->env, 0);
	while (ad->env)
	{
		ft_printf("*ad.env.key=|%s|\n", ad->env->key);
		ft_printf("*ad.env.value=|%s|\n", ad->env->value);
		ad->env = ad->env->next;
	}
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
*/
	return (0);
}
