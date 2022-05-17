/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:00:45 by krioja            #+#    #+#             */
/*   Updated: 2022/05/17 20:17:08 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_next_desc(char desc)
{
	if (desc == 'c'
		|| desc == 's'
		|| desc == 'p'
		|| desc == 'd'
		|| desc == 'i'
		|| desc == 'u'
		|| desc == 'x'
		|| desc == 'X'
		|| desc == '%')
		return (1);
	return (0);
}

static int	print_spec(va_list ap, int len, char desc)
{
	if (desc == 'c')
		len = ft_printf_c(ap, len);
	if (desc == 's')
		len = ft_printf_s(va_arg(ap, char *), len);
	if (desc == 'p')
		len = ft_printf_p(va_arg(ap, unsigned long int), len);
	if (desc == 'd' || desc == 'i' )
		len = ft_printf_di(va_arg(ap, int), len);
	if (desc == 'u')
		len = ft_printf_u(va_arg(ap, unsigned int), len);
	if (desc == 'x' || desc == 'X')
		len = ft_printf_x(va_arg(ap, unsigned int), len, desc);
	if (desc == '%')
	{
		ft_putchar_fd('%', 1);
		++len;
	}
	else
		return (len);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		len;

	i = -1;
	len = 0;
	va_start(ap, str);
	while (str[++i])
	{
		while (str[i] == '%' && is_next_desc(str[i + 1]))
		{
			len = print_spec(ap, len, str[i + 1]);
			i += 2;
		}
		if (str[i] == '\0')
			break ;
		ft_putchar_fd(str[i], 1);
		++len;
	}	
	va_end(ap);
	if (str[i] == '\0')
		return (len);
	return (-1);
}
