/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:51:07 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/18 17:49:30 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_ad	ad;

	(void)ac;
	(void)av;
	while (1)
	{
		if (!get_line(&ad))
			break ;
		//get_redir(&ad);
		(void)env;
		// get_pp(env, &ad);
		ft_printf("%s\n", ad.line);
	}
	free_all(&ad);
	return (EXIT_SUCCESS);
}
