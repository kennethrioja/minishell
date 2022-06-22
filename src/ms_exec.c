/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:00:43 by krioja            #+#    #+#             */
/*   Updated: 2022/06/22 18:00:04 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exec(t_ad *ad)
{
	get_path(ad);

	int **fd;
	int	*pid;
	int	n;
	int	n_pa;

	pa_lst_fst_or_lst(&ad->pa, 0);
	n_pa = count_pa(ad);
	n = -1;
	if (n_pa > 1)
	{
		fd = malloc(sizeof(int *) * (n_pa - 1));
		while (++n < n_pa - 1)
			fd[n] = malloc(sizeof(int) * 2);
	}
	pid = malloc(sizeof(int) * n_pa);
	n = -1;
	while (++n < n_pa - 1)
	{
		if (pipe(fd[n]) == -1)
			my_exit(ad, write(2, "Error: pipe\n", 12));
	}
	n = 0;
	while (ad->pa)
	{
		pid[n] = fork();
		if (pid[n] == -1)
			my_exit(ad, write(2, "Error: fork\n", 12));
		if (pid[n] == 0)
		{
			if (ad->pa->prev)
				dup2(fd[n - 1][0], STDIN_FILENO);
			if (ad->pa->next)
				dup2(fd[n][1], STDOUT_FILENO);
			if (ad->pa->prev || ad->pa->next) // do not close anything if 1cmd
				my_close(fd, n_pa, n, 1);
			exec_redir(ad);
		}
		if (!ad->pa->prev && !ad->pa->next) // when 1cmd
			waitpid(pid[n], NULL, 0);
		if (n >= 1) // for cmds 1 and above
		{
			if (ad->pa->next) // if next, close all previous but read actual
				my_close(fd, n_pa, n, 0);
			else // if end, close all
				my_close(fd, n_pa, n, 1);
			if (n == 1) // only for cmd 1 who does waitpid pid0
				waitpid(pid[0], NULL, 0);
			// wait current pid
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
	n = -1;
	while (++n < count_pa(ad) - 1)
	{
		free(fd[n]);
		if (n == count_pa(ad) - 2)
			free(fd);
	}
	free(pid);
	return (0);
}
