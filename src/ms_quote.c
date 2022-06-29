/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:32:25 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/28 16:32:27 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO check function and echo | echo not working any more
int	pos_n_char(char *str, int n, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			n--;
		if (n == 0)
			return (i + 1);
	}
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			return (++i);
	}
	return (i);
}

int	count_quote(char *str, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == c)
			count++;
	}
	return (count);
}

int	check_quote(char *str, char c)
{
	if (count_quote(str, c) % 2 == 0)
	{
		return (1);
	}
	write(2, QUOTE_MSG, ft_strlen(QUOTE_MSG));
	write(2, &c, 1);
	write(2, EVEN_MSG, ft_strlen(EVEN_MSG));
	write(2, "\n", 1);
	return (0);
}
