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
	free(pipe->pblt);
	pa_lst_fst_or_lst(&ad->pa, 0);
}

static int	fake_heredoc(t_ad *ad)
{
	char	*tmp;

	while (1)
	{
		tmp = readline("> ");
		if (!ft_strcmp(ad->pa->redir->file, tmp))
			break ;
		if (tmp)
			free(tmp);
	}
	free(tmp);
	return (42);
}

static int	dup_exec_close(t_ad *ad, t_pipe *pipe, int n)
{
	// check si on a besoin de && !ad->pa->next
	// ft_printf("adpacmd=|%s|\n",ad->pa->cmd);
//	ft_printf("adparedirop=|%s|\n",ad->pa->redir->op);
//	ft_printf("adparedirfile=|%s|\n",ad->pa->redir->file);
	if (is_builtins(ad) && !ad->pa->next)
		return (ms_exec_builtins(ad, pipe, n));
	if ((!ad->pa->cmd || !ad->pa->cmd[0]))
	{
		if (ad->pa->redir)
		{
			if (!ad->pa->redir->file[0])
				return (write(2, "adsh: syntax error near unexpected token `newline'\n", 51));
			else if (!ft_strcmp(ad->pa->redir->op, ">"))
				return (open(ad->pa->redir->file, O_RDWR | O_CREAT, 0644));
			else if (!ft_strcmp(ad->pa->redir->op, "<<"))
				return (fake_heredoc(ad));
		}
		return (write(2, "adsh: syntax error near unexpected token `|'\n", 45));
	}
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
			{
				custom_err(ad, 0, NOT_FOUND_CMD_MSG);
				exit(EXIT_FAILURE);
			}
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
	n = 0;
	pa_lst_fst_or_lst(&ad->pa, 0);
	while (n < pipe.n_pa)
	{
		if (ad->pa->cmd)
		{
			waitpid(pipe.pid[n], &g_status_exit, 0);
			if (WIFSIGNALED(g_status_exit))
				g_status_exit = SIGNAL_ERR + g_status_exit;
		}
		if (ad->pa->next)
			ad->pa = ad->pa->next;
		else
			break ;
		n++;
	}
	free_pipe(ad, &pipe);
	return (0);
}
