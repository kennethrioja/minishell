/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:54:32 by krioja            #+#    #+#             */
/*   Updated: 2022/05/17 20:21:49 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *str, ...);
int		ft_printf_c(va_list ap, int len);
int		ft_printf_s(char *s, int len);
int		ft_printf_di(int di, int len);
int		ft_printf_u(unsigned int u, int len);
int		ft_printf_p(unsigned long int p, int len);
int		ft_printf_x(unsigned int x, int len, char desc);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_printf_strlen(const char *s);

#endif
