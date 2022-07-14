/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:51:07 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/07/06 18:30:49 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_arg(t_ad ad)
{
	int	i;

	while (ad.pa)
	{
		printf("cmd[%s]\n", ad.pa->cmd);
		i = -1;
		while (ad.pa->args[++i])
			printf("arg%d[%s]\n", i, ad.pa->args[i]);
		while (ad.pa->redir)
		{
			printf("redir op[%s] file[%s]\n", ad.pa->redir->op,
				ad.pa->redir->file);
			ad.pa->redir = ad.pa->redir->next;
		}
		redir_lst_fst_or_lst(&ad.pa->redir, 0);
		ad.pa = ad.pa->next;
	}
	ad.pa = ad.pa_head;
}

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
		if (tmp == 2 || tmp == 3)
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
