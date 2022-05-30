/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:51:07 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/25 19:31:48 by krioja           ###   ########.fr       */
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
		if (ms_split(&ad)) // put ! to check for leaks
			break ;
		(void)env;
		ft_printf("%s\n", ad.line);
	}
	free_all(&ad);
	return (EXIT_SUCCESS);
}
