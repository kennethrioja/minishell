/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pa_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:30:15 by krioja            #+#    #+#             */
/*   Updated: 2022/05/25 16:32:40 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pa	*pa_lstnew(struct s_pa *previous)
{
	t_pa	*pa;
	
	pa = malloc(sizeof(t_pa));
	if (!pa)
		return (NULL);
	pa->cmd = NULL;
	pa->path = NULL;
	pa->args = NULL;
	if (previous)
		pa->prev = previous;
	else
		pa->prev = NULL;
	pa->next = NULL;
	return (pa);
}

void	pa_lst_fst_or_lst(t_pa **pa, int flag)
{
	if (flag == 0)
	{
		while (*pa)
		{
			if ((*pa)->prev == NULL)
				break ;
			*pa = (*pa)->prev;
		}
	}
	else
	{
		while (*pa)
		{
			if ((*pa)->next == NULL)
				break ;
			*pa = (*pa)->next;
		}
	}
}

void	pa_lstadd_back(t_pa **alst, t_pa *next)
{
	if (*alst)
	{
		pa_lst_fst_or_lst(alst, 1);
		(*alst)->next = next;
	}
	else
		*alst = next;
}
