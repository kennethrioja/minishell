/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:00:41 by krioja            #+#    #+#             */
/*   Updated: 2022/05/31 20:17:54 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_exit(t_ad *ad, int flag)
{
	free_all(ad);
	exit(flag);
}

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

void	free_cmd(t_ad *ad)
{
	free(ad->line);
	free_redir(ad);
	free_pa(ad);
	ad->pa = NULL;
	ad->redir = NULL;
}

void	free_all(t_ad *ad)
{
	while (ad->env && ad->env->next)
	{
		free(ad->env->key);
		free(ad->env->value);
		ad->env = ad->env->next;
		free(ad->env->prev);
	}
	free(ad->env->key);
	free(ad->env->value);
	free(ad->env);
}
