/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:51:07 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/22 18:53:30 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_ad	ad;

	while (1)
	{
		if (!get_line(&ad))
			break ;
		get_signal();
		// check_line(&ad);
		// get_redir(&ad);
		// get_pp(env, &ad);
		// ft_printf("%s\n", ad.line);
	}
	free_all(&ad);
	(void)ac;
	(void)av;
	(void)env;
	return (EXIT_SUCCESS);
}
