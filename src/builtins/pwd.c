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

	if (getcwd(buf, PATH_MAX))
		ft_printf("%s\n", buf);
	ad->status_exit = SUCCESS;
}
