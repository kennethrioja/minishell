/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:55:46 by krioja            #+#    #+#             */
/*   Updated: 2022/05/17 20:21:01 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_c(va_list ap, int len)
{
	char	c;

	c = va_arg(ap, int);
	ft_putchar_fd(c, 1);
	return (++len);
}

int	ft_printf_s(char *s, int len)
{
	if (!s)
	{
		ft_putstr_fd("(null)", 1);
		return (len + 6);
	}
	ft_putstr_fd(s, 1);
	return (len + ft_printf_strlen(s));
}
