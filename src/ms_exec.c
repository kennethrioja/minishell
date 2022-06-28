/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:00:43 by krioja            #+#    #+#             */
/*   Updated: 2022/06/22 19:13:14 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_pipe(t_ad *ad, t_pipe *pipe)
{
	int	n;

	n = -1;
	pa_lst_fst_or_lst(&ad->pa, 0);
	while (++n < count_pa(ad) - 1)
	{
		free(pipe->fd[n]);
		if (n == count_pa(ad) - 2)
			free(pipe->fd);
	}
	free(pipe->pid);
	pa_lst_fst_or_lst(&ad->pa, 0);
}

//TODO do not fork when builtins
static void	dup_exec_close(t_ad *ad, t_pipe *pipe, int n)
{
	if (is_builtins(ad))
		check_builtins(ad);
	else
	{
		pipe->pid[n] = fork();
		if (pipe->pid[n] == -1)
			my_exit(ad, write(2, "Error: fork\n", 12));
		if (pipe->pid[n] == 0)
		{
			if (ad->pa->prev)
				dup2(pipe->fd[n - 1][0], STDIN_FILENO);
			if (ad->pa->next)
				dup2(pipe->fd[n][1], STDOUT_FILENO);
			if (ad->pa->prev || ad->pa->next)
				my_close(pipe->fd, pipe->n_pa, n, 1);
			exec_redir(ad);
		}
	}
	if (n >= 1)
	{
		if (ad->pa->next)
			my_close(pipe->fd, pipe->n_pa, n, 0);
		else
			my_close(pipe->fd, pipe->n_pa, n, 1);
	}
}

static void	init_pipe(t_ad *ad, t_pipe *pip)
{
	int	n;

	n = -1;
	pip->n_pa = count_pa(ad);
	if (pip->n_pa > 1)
	{
		pip->fd = malloc(sizeof(int *) * (pip->n_pa - 1));
		while (++n < pip->n_pa - 1)
			pip->fd[n] = malloc(sizeof(int) * 2);
	}
	pip->pid = malloc(sizeof(int) * pip->n_pa);
	n = -1;
	while (++n < pip->n_pa - 1)
	{
		if (pipe(pip->fd[n]) == -1)
			my_exit(ad, write(2, "Error: pipe\n", 12));
	}
}

int	ms_exec(t_ad *ad)
{
	t_pipe	pipe;
	int		n;

//	set_path(ad);
	init_pipe(ad, &pipe);
	n = 0;
	while (ad->pa)
	{
		dup_exec_close(ad, &pipe, n);
		if (ad->pa->next)
		{
			++n;
			ad->pa = ad->pa->next;
		}
		else
			break ;
	}
	n = -1;
	while (++n < pipe.n_pa)
	{
		if (ad->pa->is_blt == 0)
		{
			waitpid(pipe.pid[n], &g_status_exit, 0);
			if (WIFSIGNALED(g_status_exit))
				g_status_exit = SIGNAL_ERR + g_status_exit;
		}
	}
	free_pipe(ad, &pipe);
	return (0);
}
