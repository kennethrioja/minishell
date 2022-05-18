/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:51:07 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/18 10:54:51 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_all(t_ad *ad)
{
	free(ad->line);
}

int	main(int ac, char **av, char **env)
{
	t_ad	ad;

	(void)ac;
	(void)av;
	while (1)
	{
		if (!get_line(&ad))
			break ;
		get_path_and_params(env, &ad);
		ft_printf("%s\n", ad.line);
	}
	free_all(&ad);
	return (EXIT_SUCCESS);
}
