/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:51:07 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/28 12:11:55 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_ad	ad;
	int		tmp;

	init(&ad, env);
	while (1)
	{
		handle_signal();
		if (!get_line(&ad))
			break ;
		tmp = ms_split(&ad);
		if (tmp == 1)
			break ;
		if (tmp == 2)
			continue ;
		if (ms_exec(&ad))
			break ;
		free_pa(&ad);
		free(ad.line);
	}
	free_env(&ad);
	free(ad.line);
	(void)ac;
	(void)av;
	(void)env;
	return (EXIT_SUCCESS);
}
