/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:03:18 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/03 15:03:20 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*split_path(t_node *path)
{
	t_node	*new;
	int		size;
	char	*key;

	size = 0;
	new = NULL;
	while (ft_strlen_c(path->value + size, ':'))
	{
		//TODO use ft_split maybe ?????????
		printf(":%zu size%d\n", ft_strlen_c(path->value + size, ':'), size);
		key = ft_substr(path->value, size, ft_strlen_c(path->value + size, ':'));
		ft_printf("%s\n", key);
		path->value = path->value + size + 1;
		size += ft_strlen_c(path->value, ':') + 1;
		append_env(&new, key, NULL);
		printf(":%zu size%d\n", ft_strlen_c(path->value + size, ':'), size);
	}
//	while (new)
//	{
//		ft_printf("%s\n", new->key);
//		new = new->next;
//	}
	return (new);
}

void	check_path(t_ad *ad)
{
	t_node	*path;

	path = split_path(get_env(ad, get_i_env(ad, "PATH")));
//	split_path();
}
