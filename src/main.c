/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:51:07 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/31 20:35:51 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_ad	ad;

	init_env(&ad, env);
	while (1)
	{
		handle_signal();
		if (!get_line(&ad))
			break ;
//		if (ms_split(&ad))
//			break ;
		check_line(&ad);
		free(ad.line);
//		get_redir(&ad);
//		get_pp(env, &ad);
//		ft_printf("%s\n", ad.line);
//		ft_printf("%s\n", ad.line);
	}
	free_all(&ad);
	(void)ac;
	(void)av;
	return (EXIT_SUCCESS);
}
// put !ms_split to check for leaks
