/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:09:23 by krioja            #+#    #+#             */
/*   Updated: 2022/05/18 18:58:59 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*redir_lstnew(s_redir *previous)
{
	t_redir	*redir;
	
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->op = NULL;
	redir->file = NULL;
	if (!previous)
		redir->prev = NULL;
	else
		redir->prev = prev;
	redir->next = NULL;
	return (redir);
}

t_redir	*redir_lstlast(t_redir *redir)
{
	while (redir)
	{
		if (redir->next == NULL)
			break ;
		redir = lst->next;
	}
	return (redir);
}

void	redir_lstfirst(t_redir *redir)
{
	while (redir)
	{
		if (redir->prev == NULL)
			break ;
		redir = lst->prev;
	}
}

void	redir_lstadd_back(t_redir **redir, t_redir *redirnew)
{
	t_redir	*last;

	if (*redir)
	{
		last = redir_lstlast(*redir);
		last->next = redirnew;
	}
	else
	{
		*redir = redirnew;
	}
}
