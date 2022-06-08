/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:11:14 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/04 17:34:17 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_line(t_ad *ad)
{
	struct termios	saved;
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &saved);
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
	ad->line = readline("adsh> ");
	if (ad->line)
		add_history(ad->line);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);
	if (!ad->line)
		return (0);
	return (1);
}

void	check_line(t_ad *ad)
{
//	printf("%s\n", ad->pa->cmd);
	if (!ft_strcmp("echo", ad->pa->cmd))
		ft_echo(ad);
//	else if (!ft_strcmp("cd", ad->pa->cmd))
//		ft_cd(ad);
//	else if (!ft_strcmp("pwd", ad->pa->cmd))
//		ft_pwd(ad);
//	else if (!ft_strcmp("export", ad->pa->cmd))
//		ft_export(ad);
//	else if (!ft_strcmp("unset", ad->pa->cmd))
//		ft_unset(ad);
//	else if (!ft_strcmp("env", ad->pa->cmd))
//		ft_env(ad);
//	else if (!ft_strcmp("exit", ad->pa->cmd))
//	{
//		ft_printf("exit\n");
//		exit(EXIT_SUCCESS);
//	}
//	else
//		check_path(ad);
	// 	write(2, "adsh: command not found\n", 25);
}
