/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:58:03 by krioja            #+#    #+#             */
/*   Updated: 2022/06/22 17:58:20 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pa(t_ad *ad)
{
	int	n;

	n = 0;
	pa_lst_fst_or_lst(&ad->pa, 0);
	while (ad->pa)
	{
		++n;
		if (ad->pa->next)
			ad->pa = ad->pa->next;
		else
			break ;
	}
	pa_lst_fst_or_lst(&ad->pa, 0);
	return (n);
}

void	my_close(int **fd, int n_pa, int n, int flag)
{
	int	i;

	i = 0;

	while (i <= n && flag == 0)
	{
		if (i != n)
			close(fd[i][0]);
		close(fd[i][1]);
		++i;
	}
	while (i < n_pa - 1 && flag == 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		++i;
	}
}
