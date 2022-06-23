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
	ad->line = readline(ft_strjoin(SHELL_NAME, "> "));
	if (ad->line)
		add_history(ad->line);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);
	if (!ad->line)
		return (0);
	return (1);
}

void	check_line(t_ad *ad)
{
	if (ad->pa->cmd == NULL)
		return ;
	ad->pa->cmd = ft_strtolower(ad->pa->cmd);
	if (!ad->pa)
		return ;
	if (!ft_strcmp("echo", ad->pa->cmd))
		ft_echo(ad);
	else if (!ft_strcmp("cd", ad->pa->cmd))
		ft_cd(ad);
	else if (!ft_strcmp("pwd", ad->pa->cmd))
		ft_pwd();
	else if (!ft_strcmp("env", ad->pa->cmd))
		ft_env(ad);
	else if (!ft_strcmp("export", ad->pa->cmd))
		ft_export(ad);
	else if (!ft_strcmp("unset", ad->pa->cmd))
		ft_unset(ad);
	else if (!ft_strcmp("exit", ad->pa->cmd))
		ft_exit(ad);
	else
		if (check_path(ad) == 1)
			custom_err(ad, 0, NOT_FOUND_CMD_MSG);
}
