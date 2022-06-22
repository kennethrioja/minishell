/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:00:43 by krioja            #+#    #+#             */
/*   Updated: 2022/06/22 10:57:34 by krioja           ###   ########.fr       */
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
*/
static int	count_pa(t_ad *ad)
{
	int	n;

	n = 0;
	pa_lst_fst_or_lst(&ad->pa, 0);
	while (ad->pa)
	{
		++n;
		if (ad->pa->next)
			ad->pa = ad->pa->next;
		else
			break ;
	}
	pa_lst_fst_or_lst(&ad->pa, 0);
	return (n);
}

static void	my_close(int **fd, int n_pa)
{
	int	i;

	i = -1;
	while (++i < n_pa - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

int	ms_exec(t_ad *ad)
{
	get_path(ad);
//	exec_redir(ad);

	int **fd;
	int	*pid;
	int	n;
	int	n_pa;

	pa_lst_fst_or_lst(&ad->pa, 0);
	n_pa = count_pa(ad);
	ft_printf("pa=%d\n", n_pa);
	n = -1;
	if (n_pa > 1)
	{
		fd = malloc(sizeof(int *) * (n_pa - 1));
		while (++n < n_pa - 1)
		{
			ft_printf("malloc fd[%d]\n", n);
			fd[n] = malloc(sizeof(int) * 2);
		}
	}
	pid = malloc(sizeof(int) * n_pa);
	n = -1;
	while (++n < n_pa - 1)
	{
		ft_printf("pipe(fd[%d])\n", n);
		if (pipe(fd[n]) == -1)
			my_exit(ad, write(2, "Error: pipe\n", 12));
	}
	ft_printf("n=%d\n", n);


	n = 0;
	while (ad->pa)
	{
		pid[n] = fork();
		if (pid[n] == -1)
			my_exit(ad, write(2, "Error: fork\n", 12));
		if (pid[n] == 0)
		{
			if (ad->pa->prev || ad->pa->next)
			{
				if (ad->pa->prev)
				{
					ft_printf("cmd: %s, STDIN on fd[%d][0]\n", ad->pa->args[0], n-1);
					dup2(fd[n - 1][0], STDIN_FILENO);
				}
				if (ad->pa->next)
				{
					ft_printf("cmd: %s, STDOUT on fd[%d][1]\n", ad->pa->args[0], n);
					dup2(fd[n][1], STDOUT_FILENO);
				}
				my_close(fd, n_pa);
			}
			exec_redir(ad);
		}

		
		if (n > 0)
		{
			my_close(fd, n_pa);
			if (n == 1)
			{
				ft_printf("%d waits pid[0]\n",n);
				waitpid(pid[0], NULL, 0);
			}
			ft_printf("%d waits pid[%d]\n",n,n);
			waitpid(pid[n], NULL, 0);
		}
		if (!ad->pa->prev && !ad->pa->next)
		{
			ft_printf("%d waits\n",n);
			waitpid(pid[n], NULL, 0);
		}


		if (ad->pa->next)
		{
			++n;
			ad->pa = ad->pa->next;
		}
		else
			break ;
	}

	pa_lst_fst_or_lst(&ad->pa, 0);
	ft_printf("pa=%d\n", count_pa(ad));
	n = -1;
	while (++n < count_pa(ad) - 1)
	{
		ft_printf("free(fd[%d])\n", n);
		free(fd[n]);
		if (n == count_pa(ad) - 2)
			free(fd);
	}
	free(pid);

	/*
// TWO COMMANDS
//————
//0

	pid[0] = fork();
	if (pid[0] == -1)
		my_exit(ad, write(2, "Error: fork\n", 12));
	if (pid[0] == 0)
	{
		ft_printf("cmd: %s, STDOUT on fd[0][1]\n", ad->pa->args[0]);
		dup2(fd[0][1], STDOUT_FILENO);
		close(fd[0][1]);
		close(fd[0][0]);
		exec_redir(ad);
	}

//————
//1

	if (ad->pa->next)
		ad->pa = ad->pa->next;

	pid[1] = fork();
	if (pid[1] == -1)
		my_exit(ad, write(2, "Error: fork\n", 12));
	if (pid[1] == 0)
	{
		ft_printf("cmd: %s, STDIN on fd[0][0]\n", ad->pa->args[0]);
		dup2(fd[0][0], STDIN_FILENO);
		close(fd[0][0]);
		close(fd[0][1]);
		exec_redir(ad);
	}


	close(fd[0][0]);
	close(fd[0][1]);
	ft_printf("waits pid[0]\n");
	waitpid(pid[0], NULL, 0);
	ft_printf("waits pid[1]\n");
	waitpid(pid[1], NULL, 0);
*/

/*
// THREE COMMANDS
	int	fd[3][2];
	int	pid0;
	int	pid1;
	int	pid2;
	int	pid3;

	pa_lst_fst_or_lst(&ad->pa, 0);

	if (pipe(fd[0]) == -1 || pipe(fd[1]) == -1)
		my_exit(ad, write(2, "Error: pipe\n", 12));

//0	
	pid0 = fork();
	if (pid0 == -1)
		my_exit(ad, write(2, "Error: fork\n", 12));
	if (pid0 == 0)
	{
		ft_printf("pid0.exe:%s\n",ad->pa->args[0]);
		dup2(fd[0][1], STDOUT_FILENO);
		close(fd[0][1]);
		close(fd[0][0]);
		exec_redir(ad);
	}
	
//1
	if (ad->pa->next)
		ad->pa = ad->pa->next;

	pid1 = fork();
	if (pid1 == -1)
		my_exit(ad, write(2, "Error: fork\n", 12));
	if (pid1 == 0)
	{
		ft_printf("pid1.exe:%s\n",ad->pa->args[0]);
		dup2(fd[0][0], STDIN_FILENO);
		if (ad->pa->next)
		{
			ft_printf("1 has next\n");
			dup2(fd[1][1], STDOUT_FILENO);
		}
		close(fd[0][0]);
		close(fd[0][1]);
		exec_redir(ad);
	}
	close(fd[0][0]);
	close(fd[0][1]);
	waitpid(pid0, NULL, 0);
	waitpid(pid1, NULL, 0);

//2
	if (ad->pa->next)
		ad->pa = ad->pa->next;

	pid2 = fork();
	if (pid2 == -1)
		my_exit(ad, write(2, "Error: fork\n", 12));
	if (pid2 == 0)
	{
		ft_printf("pid2.exe:%s\n",ad->pa->args[0]);
		dup2(fd[1][0], STDIN_FILENO);
		if (ad->pa->next)
		{
			ft_printf("2 has next\n");
			dup2(fd[2][1], STDOUT_FILENO);
		}
		close(fd[1][0]);
		close(fd[1][1]);
		exec_redir(ad);
	}
	close(fd[1][0]);
	close(fd[1][1]);
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
		dup2(fd[2][0], STDIN_FILENO);
		close(fd[2][0]);
		close(fd[2][1]);
		exec_redir(ad);
	}
	
	close(fd[2][0]);
	close(fd[2][1]);
	waitpid(pid3, NULL, 0);
*/

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
