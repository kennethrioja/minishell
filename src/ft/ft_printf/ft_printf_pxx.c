/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:25:39 by krioja            #+#    #+#             */
/*   Updated: 2022/05/17 20:16:07 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	puthex(unsigned long int hex, int len, int caps)
{
	char	*hex_str;

	if (hex == 0)
		return (len);
	if (caps == 0)
	{
		hex_str = "0123456789abcdef";
		len = puthex(hex / 16, len, 0);
		ft_putchar_fd(hex_str[hex % 16], 1);
		return (++len);
	}
	hex_str = "0123456789ABCDEF";
	len = puthex(hex / 16, len, 1);
	ft_putchar_fd(hex_str[hex % 16], 1);
	return (++len);
}

int	ft_printf_p(unsigned long int p, int len)
{
	ft_putstr_fd("0x", 1);
	len += 2;
	if (p == 0)
	{
		ft_putchar_fd('0', 1);
		return (++len);
	}
	return (puthex(p, len, 0));
}

int	ft_printf_x(unsigned int x, int len, char desc)
{
	if (x == 0)
	{
		ft_putchar_fd('0', 1);
		return (++len);
	}
	if (desc == 'x')
		len = puthex(x, len, 0);
	else if (desc == 'X')
		len = puthex(x, len, 1);
	return (len);
}
