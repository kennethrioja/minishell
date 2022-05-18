/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 08:48:24 by krioja            #+#    #+#             */
/*   Updated: 2022/05/17 20:24:21 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_printf_strlen(s));
}

int	ft_printf_strlen(const char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}
