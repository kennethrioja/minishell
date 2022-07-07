/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:00:43 by krioja            #+#    #+#             */
/*   Updated: 2022/07/06 19:56:45 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_exec(t_ad *ad)
{
	if (ad->pa->redir && ad->pa->cmd && ad->pa->redir->op
		&& !ad->pa->redir->file[0])
		return (custom_err_ret(NL_MSG, 130, 1));
	if ((ad->pa->prev || ad->pa->next) && (!ad->pa->cmd || !ad->pa->cmd[0]))
		return (custom_err_ret(PIPE_MSG, 2, 1));
	if ((!ad->pa->cmd || !ad->pa->cmd[0]))
	{
		if (ad->pa->redir)
		{
			if (!ad->pa->redir->file[0])
			{
				g_status_exit = 130;
				return (write(2, NL_MSG, ft_strlen(NL_MSG)));
			}
			else if (!ft_strcmp(ad->pa->redir->op, ">"))
				return (open(ad->pa->redir->file, O_RDWR | O_CREAT, 0644));
			else if (!ft_strcmp(ad->pa->redir->op, "<<"))
				return (fake_heredoc(ad));
		}
		return (1);
	}
	return (0);
}

static int	dup_exec_close(t_ad *ad, t_pipe *pipe, int n)
{
	if (check_exec(ad))
		return (1);
	else if (is_builtins(ad) && !ad->pa->next)
		return (ms_exec_builtins(ad, pipe, n));
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
			if (ms_exec_check_execve(ad))
				custom_err_exit(ad, 0,
					NOT_FOUND_CMD_MSG, EXIT_FAILURE);
		}
		my_close(ad, pipe, n);
		return (0);
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
	pip->pblt = malloc(sizeof(int) * 2);
	if (pipe(pip->pblt) == -1)
		my_exit(ad, write(2, "Error: builtins pipe\n", 21));
}

static void	wait_pipe(t_ad *ad, t_pipe *pip)
{
	int	n;

	n = 0;
	pa_lst_fst_or_lst(&ad->pa, 0);
	while (n < pip->n_pa)
	{
		if (ad->pa->cmd)
		{
			waitpid(pip->pid[n], &g_status_exit, 0);
			if (WIFSIGNALED(g_status_exit))
				g_status_exit = SIGNAL_ERR + g_status_exit;
			else if (WIFEXITED(g_status_exit))
				g_status_exit = WEXITSTATUS(g_status_exit);
		}
		if (ad->pa->next)
			ad->pa = ad->pa->next;
		else
			break ;
		n++;
	}
}

int	ms_exec(t_ad *ad)
{
	t_pipe	pipe;
	int		n;

	init_pipe(ad, &pipe);
	n = 0;
	pa_lst_fst_or_lst(&ad->pa, 0);
	while (ad->pa)
	{
		if (dup_exec_close(ad, &pipe, n))
			break ;
		if (ad->pa->next)
		{
			++n;
			ad->pa = ad->pa->next;
		}
		else
			break ;
	}
	wait_pipe(ad, &pipe);
	free_pipe(ad, &pipe);
	return (0);
}
