/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:08:29 by krioja            #+#    #+#             */
/*   Updated: 2022/05/17 20:15:54 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	putnbr_di(int di, int len)
{
	if (di == -2147483648)
	{
		ft_putstr_fd("-2147483648", 1);
		return (len + 11);
	}
	if (di < 0)
	{
		ft_putchar_fd('-', 1);
		++len;
		di *= -1;
	}
	if (di < 10)
	{
		ft_putchar_fd('0' + di, 1);
		return (++len);
	}
	len = putnbr_di(di / 10, ++len);
	ft_putchar_fd('0' + di % 10, 1);
	return (len);
}

int	ft_printf_di(int di, int len)
{
	len = putnbr_di(di, len);
	return (len);
}

static int	putnbr_u(unsigned int u, int len)
{
	if (u == 0)
		return (len);
	else
	{
		len = putnbr_u(u / 10, len);
		ft_putchar_fd('0' + u % 10, 1);
		return (++len);
	}
}

int	ft_printf_u(unsigned int u, int len)
{
	if (u == 0)
	{
		ft_putchar_fd('0', 1);
		return (++len);
	}
	len = putnbr_u(u, len);
	return (len);
}
