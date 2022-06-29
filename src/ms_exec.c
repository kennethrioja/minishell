/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:00:43 by krioja            #+#    #+#             */
/*   Updated: 2022/06/28 13:31:33 by krioja           ###   ########.fr       */
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

static void	dup_exec_close(t_ad *ad, t_pipe *pipe, int n)
{
	if (is_builtins(ad) && !ad->pa->next)
		ms_exec_builtins(ad, pipe, n);
	else
	{
		pipe->pid[n] = fork();
		handle_child_signal();
		if (pipe->pid[n] == -1)
			my_exit(ad, write(2, "Error: fork\n", 12));
		if (pipe->pid[n] == 0)
		{
			if (ad->pa->prev && !ad->pa->is_blt)
				dup2(pipe->fd[n - 1][0], STDIN_FILENO);
			if (ad->pa->next)
				dup2(pipe->fd[n][1], STDOUT_FILENO);
			if ((ad->pa->prev && !ad->pa->is_blt) || ad->pa->next)
				my_close2(pipe->fd, pipe->n_pa, n, 1);
			if (ms_exec_check_execve(ad, pipe, n))
			{
				custom_err(ad, 0, NOT_FOUND_CMD_MSG);
				exit(EXIT_FAILURE);
			}
		}
		my_close(ad, pipe, n);
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

static int	find_last_blt(t_ad *ad)
{
	t_pa	*tmp;
	int		ret;
	int		n;

	ret = 0;
	n = 0;
	tmp = NULL;
	pa_lst_fst_or_lst(&ad->pa, 0);
	while (ad->pa)
	{
		if (ad->pa->is_blt == 1)
		{
			tmp = ad->pa;
			ret = n;
		}
		n++;
		ad->pa = ad->pa->next;
	}
	if (tmp)
		ad->pa = tmp;
	else
		ad->pa = ad->pa_head;
	return (ret);
}

int	ms_exec(t_ad *ad)
{
	t_pipe	pipe;
	int		n;

	init_pipe(ad, &pipe);
	n = find_last_blt(ad);
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
	n = find_last_blt(ad);
	while (n < pipe.n_pa)
	{
		waitpid(pipe.pid[n], &g_status_exit, 0);
		if (WIFSIGNALED(g_status_exit))
			g_status_exit = SIGNAL_ERR + g_status_exit;
		ad->pa = ad->pa->next;
		n++;
	}
	free_pipe(ad, &pipe);
	return (0);
}
