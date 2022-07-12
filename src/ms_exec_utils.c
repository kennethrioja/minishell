/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:58:03 by krioja            #+#    #+#             */
/*   Updated: 2022/07/06 19:07:47 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pa(t_ad *ad)
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

void	my_close2(int **fd, int n_pa, int n, int flag)
{
	int	i;

	i = 0;
	while (i <= n && flag == 0)
	{
		if (i != n)
			close(fd[i][0]);
		close(fd[i][1]);
		++i;
	}
	while (i < n_pa - 1 && flag == 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		++i;
	}
}

void	my_close(t_ad *ad, t_pipe *pipe, int n)
{
	if (n >= 1)
	{
		if (!ad->pa->next)
			my_close2(pipe->fd, pipe->n_pa, n, 1);
		else
			my_close2(pipe->fd, pipe->n_pa, n, 0);
	}
	if (pipe->pblt[1])
	{
		close(pipe->pblt[0]);
		close(pipe->pblt[1]);
	}
}

int	fake_heredoc(t_ad *ad)
{
	char	*tmp;

	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
		{
			write(2, "adsh: warning: here-document end-of-file (wanted `", 50);
			write(2, ad->pa->redir->file, ft_strlen(ad->pa->redir->file));
			write(2, "')\n", 3);
			break ;
		}
		if (!ft_strcmp(ad->pa->redir->file, tmp))
			break ;
		if (tmp)
			free(tmp);
	}
	if (tmp)
		free(tmp);
	return (42);
}

void	free_pipe(t_ad *ad, t_pipe *pipe)
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
