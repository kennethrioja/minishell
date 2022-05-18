/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:08:32 by krioja            #+#    #+#             */
/*   Updated: 2022/05/18 16:26:25 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_lstnew(t_pa *pa)
{
	pa = malloc(sizeof(t_pa));
	if (!pa)
		return (NULL);
	pa->next = NULL;
	return (pa);
}

t_pa	*ms_lstlast(t_pa *pa)
{
	while (pa)
	{
		if (pa->next == NULL)
			break ;
		pa = lst->next;
	}
	return (pa);
}

void	ms_lstadd_back(t_pa **pa, t_pa *panew)
{
	t_pa	*last;

	if (*pa)
	{
		last = ms_lstlast(*pa);
		last->next = panew;
	}
	else
	{
		*pa = panew;
	}
	return ;
}
