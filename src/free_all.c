/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:00:41 by krioja            #+#    #+#             */
/*   Updated: 2022/05/24 21:02:05 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redir(t_ad *ad)
{
	while (ad->redir && ad->redir->next)
	{
		if (ad->redir->op)
			free(ad->redir->op);
		if (ad->redir->file)
			free(ad->redir->file);
		ad->redir = ad->redir->next;
		free(ad->redir->prev);
	}
	free(ad->redir);
}

static void	free_pa(t_ad *ad)
{
	int	n;

	n = -1;
	while (ad->pa && ad->pa->next)
	{
		if (ad->pa->cmd)
			free(ad->pa->cmd);
		if (ad->pa->path)
			free(ad->pa->path);
		while (ad->pa->args[++n])
			free(ad->pa->args[n]);
		ad->pa = ad->pa->next;
		free(ad->pa->prev);
	}
	free(ad->pa);
}

void	free_all(t_ad *ad)
{
	free(ad->line);
	free_redir(ad);
	free_pa(ad);
}
