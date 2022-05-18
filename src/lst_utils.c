/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:08:32 by krioja            #+#    #+#             */
/*   Updated: 2022/05/18 15:30:51 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_lstnew(t_pp *pp)
{
	pp = malloc(sizeof(t_pp));
	if (!pp)
		return (NULL);
	pp->next = NULL;
	return (pp);
}

t_pp	*ms_lstlast(t_pp *pp)
{
	while (pp)
	{
		if (pp->next == NULL)
			break ;
		pp = lst->next;
	}
	return (pp);
}

void	ms_lstadd_back(t_pp **pp, t_pp *ppnew)
{
	t_pp	*last;

	if (*pp)
	{
		last = ms_lstlast(*pp);
		last->next = ppnew;
	}
	else
	{
		*pp = ppnew;
	}
	return ;
}
