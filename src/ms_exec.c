/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:00:43 by krioja            #+#    #+#             */
/*   Updated: 2022/06/21 20:59:23 by krioja           ###   ########.fr       */
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

int	ms_exec(t_ad *ad)
{
	get_path(ad);
//	exec_redir(ad);


	int	fd[2][2];
	int	pid1;
	int	pid2;
	int	pid3;

	pa_lst_fst_or_lst(&ad->pa, 0);

	if (pipe(fd[0]) == -1 || pipe(fd[1]) == -1)
		my_exit(ad, write(2, "Error: pipe\n", 12));
//1	
	pid1 = fork();
	if (pid1 == -1)
		my_exit(ad, write(2, "Error: fork\n", 12));
	if (pid1 == 0)
	{
		ft_printf("pid1.exe:%s\n",ad->pa->args[0]);
		dup2(fd[0][1], STDOUT_FILENO);
		close(fd[0][1]);
		close(fd[0][0]);
		exec_redir(ad);
	}
	
//2
	if (ad->pa->next)
		ad->pa = ad->pa->next;

	pid2 = fork();
	if (pid2 == -1)
		my_exit(ad, write(2, "Error: fork\n", 12));
	if (pid2 == 0)
	{
		ft_printf("pid2.exe:%s\n",ad->pa->args[0]);
		dup2(fd[0][0], STDIN_FILENO);
		if (ad->pa->next)
		{
			ft_printf("2 has next\n");
			dup2(fd[1][1], STDOUT_FILENO);
		}
		close(fd[0][0]);
		close(fd[0][1]);
		exec_redir(ad);
	}
	close(fd[0][0]);
	close(fd[0][1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	
//3
	if (ad->pa->next)
		ad->pa = ad->pa->next;
	
	pid3 = fork();
	if (pid3 == -1)
		my_exit(ad, write(2, "Error: fork\n", 12));
	if (pid3 == 0)
	{
		ft_printf("pid3.exe:%s\n",ad->pa->args[0]);
		dup2(fd[1][0], STDIN_FILENO);
		close(fd[1][0]);
		close(fd[1][1]);
		exec_redir(ad);
	}
	
	close(fd[1][0]);
	close(fd[1][1]);
	waitpid(pid3, NULL, 0);

	return (0);
}
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
