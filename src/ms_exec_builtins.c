/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:34:44 by krioja            #+#    #+#             */
/*   Updated: 2022/06/28 13:01:20 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_blt(t_ad *ad)
{
	ad->pa->cmd = ft_strtolower(ad->pa->cmd);
	if (!ft_strcmp("echo", ad->pa->cmd))
		return (ft_echo(ad));
	else if (!ft_strcmp("cd", ad->pa->cmd))
		return (ft_cd(ad));
	else if (!ft_strcmp("pwd", ad->pa->cmd))
		return (ft_pwd());
	else if (!ft_strcmp("env", ad->pa->cmd))
		return (ft_env(ad));
	else if (!ft_strcmp("export", ad->pa->cmd))
		return (ft_export(ad));
	else if (!ft_strcmp("unset", ad->pa->cmd))
		return (ft_unset(ad));
	else if (!ft_strcmp("exit", ad->pa->cmd))
		ft_exit(ad);
	return (1);
}

int	ms_exec_builtins(t_ad *ad, t_pipe *pipe, int n)
{
    // comprendre cette condition
	if (!ad->pa->next)
        pipe->pblt[1] = dup(STDOUT_FILENO);
    if (ad->pa->next)
		dup2(pipe->pblt[1], STDOUT_FILENO);
	if (ad->pa->next)
		my_close2(pipe->fd, pipe->n_pa, n, 1);
	ms_exec_redir(ad);
	if (!exec_blt(ad))
    {
        // comprendre cette condition et celle ci
        if (!ad->pa->next)
            dup2(pipe->pblt[1], STDOUT_FILENO);
		return (0);
    }
	return (1);
}
