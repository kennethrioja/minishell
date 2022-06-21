/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:51:07 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/09 21:46:52 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_ad	ad;

	init(&ad, env);
	while (1)
	{
		handle_signal();
		if (!get_line(&ad))
			break ;
		if (ms_split(&ad))
			break ;
//    if (ms_pipex(&ad))
//	   	break ;
//		while (ad.pa)
//		{
			check_line(&ad);
//			ad.pa = ad.pa->next;
//		}
//		ad.pa = ad.pa_head;
		free_cmd(&ad);
	}
	free_all(&ad);
	(void)ac;
	(void)av;
	(void)env;
	return (EXIT_SUCCESS);
}
