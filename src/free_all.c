/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:00:41 by krioja            #+#    #+#             */
/*   Updated: 2022/05/18 19:02:37 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO . free all op file first, then redir struct
void	free_redir(t_ad *ad)
{
	while (ad->redir->prev)
		redir_lstfirst(ad);
	while (ad->redir)
	{
		free(ad->redir->op);
		free(ad->redir->free);
	}
	while (ad->redir)
		redir_lstfirst(ad);
}

void	free_all(t_ad *ad)
{
	free(ad->line);
	//free_redir(ad);
	//free_pa(ad);
}
