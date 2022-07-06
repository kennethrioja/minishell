/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:00:41 by krioja            #+#    #+#             */
/*   Updated: 2022/06/09 20:10:55 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_exit(t_ad *ad, int flag)
{
	free_all(ad);
	exit(flag);
}

void	free_redir(t_ad *ad)
{
	t_redir	*next;

	redir_lst_fst_or_lst(&ad->pa->redir, 0);
	while (ad->pa->redir)
	{
		next = ad->pa->redir->next;
		free(ad->pa->redir->op);
		free(ad->pa->redir->file);
		free(ad->pa->redir);
		ad->pa->redir = next;
	}
}

void	free_pa(t_ad *ad)
{
	int		n;
	t_pa	*next;

	ad->pa = ad->pa_head;
	while (ad->pa)
	{
		next = ad->pa->next;
		free(ad->pa->cmd);
		free(ad->pa->path);
		n = -1;
		while (ad->pa->args[++n])
			free(ad->pa->args[n]);
		free(ad->pa->args);
		free_redir(ad);
		free(ad->pa);
		ad->pa = next;
	}
}

void	free_cmd(t_ad *ad)
{
	free(ad->line);
//	if (ad->redir)
//		free_redir(ad);
	free_pa(ad);
	ad->pa = NULL;
	ad->pa_head = NULL;
//	ad->redir = NULL;
}

void	free_all(t_ad *ad)
{
	free_env(ad);
//	if (ad->redir)
//		free_redir(ad);
	if (ad->pa)
		free_pa(ad);
}
