/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:00:43 by krioja            #+#    #+#             */
/*   Updated: 2022/06/20 13:15:24 by krioja           ###   ########.fr       */
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

/*
static int	count_redir(t_ad *ad)
{
	int	n;

	n = 0;
	redir_lst_fst_or_lst(&ad->pa->redir, 0);
	while (ad->pa->redir)
	{
		if (ad->pa->redir->next)
		{
			++n;
			ad->pa->redir = ad->pa->redir->next;
		}
		else
		{
			++n;
			break;
		}
	}
	return (n);
}

static int	redir_one_sm(t_ad *ad)
{
	int	pid;
	int	infile;

	pid = fork();
	if (pid == -1)
		my_exit(ad, write(2, "Error: fork\n", 12));
	if (pid == 0)
	{
		infile = open(ad->pa->redir->file, O_RDWR);
		if (infile == -1)
			my_exit(ad, write(2, "Error: open infile\n", 20));
		dup2(infile, STDIN_FILENO);
		execve(ad->pa->path, ad->pa->args, NULL);
	}
	return (pid);
}

static int	redir_one_gr(t_ad *ad)
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
			my_exit(ad, write(2, "Error: open outfile\n", 20));
		dup2(outfile, STDOUT_FILENO);
		execve(ad->pa->path, ad->pa->args, NULL);
	}
	return (pid);
}

static void	exec_redir(t_ad *ad)
{
	int	*pid_tab;
	int	n;

	n = 0;
	pid_tab = malloc(sizeof(int) * count_redir(ad));
	redir_lst_fst_or_lst(&ad->pa->redir, 0);
	while (ad->pa->redir)
	{
		ft_printf("HEYYY\n");
		if (!ft_strncmp(ad->pa->redir->op, ">", 1))
			pid_tab[n] = redir_one_gr(ad);
		else if (!ft_strncmp(ad->pa->redir->op, "<", 1))
			pid_tab[n] = redir_one_sm(ad);
		n++;
		if (ad->pa->redir->next)
			ad->pa->redir = ad->pa->redir->next;
		else
			break ;
	}
	n = -1;
	while (++n < count_redir(ad))
		waitpid(pid_tab[n], NULL, 0);
	free(pid_tab);
}
*/

int	ms_pipex(t_ad *ad)
{
//	int	pid;

	get_path(ad);
//	if (ad->pa->redir)
//		exec_redir(ad);
//	else
//	pid = fork();
//	if (pid == -1)
//		my_exit(ad, write(2, "Error: fork\n", 12));
//	if (pid == 0)
		execve(ad->pa->path, ad->pa->args, NULL);
//	waitpid(pid, NULL, 0);
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
