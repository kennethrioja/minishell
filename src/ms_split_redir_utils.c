/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_redir_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:09:23 by krioja            #+#    #+#             */
/*   Updated: 2022/05/30 10:41:55 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*redir_lstnew(struct s_redir *previous)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->op = NULL;
	redir->file = NULL;
	if (previous)
		redir->prev = previous;
	else
		redir->prev = NULL;
	redir->next = NULL;
	return (redir);
}

void	redir_lst_fst_or_lst(t_redir **redir, int flag)
{
	if (flag == 0)
	{
		while (*redir)
		{
			if ((*redir)->prev == NULL)
				break ;
			*redir = (*redir)->prev;
		}
	}
	else
	{
		while (*redir)
		{
			if ((*redir)->next == NULL)
				break ;
			*redir = (*redir)->next;
		}
	}
}

void	redir_lstadd_back(t_redir **alst, t_redir *next)
{
	if (*alst)
	{
		redir_lst_fst_or_lst(alst, 1);
		(*alst)->next = next;
		redir_lst_fst_or_lst(alst, 1);
	}
	else
		*alst = next;
}
