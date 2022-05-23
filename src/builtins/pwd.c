/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:35:22 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/23 20:01:20 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_ad *ad)
{
	char	buf[PATH_MAX];

	// if (!ad->pa->args[1])
		if (getcwd(buf, PATH_MAX))
			printf("%s\n", buf);
	// else
	// 	ft_printf("pwd: too many arguments\n");
	(void)ad;
}
