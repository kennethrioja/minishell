/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:29:34 by krioja            #+#    #+#             */
/*   Updated: 2022/06/01 19:09:50 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static int	has_op(const char *s)
//{
//	int i;
//
//	i = -1;
//	while (s[++i])
//	{
//		if (s[i] == '>' || s[i] == '<' || s[i] == '|')
//			return (1);
//	}
//	return (0);
//}

int	ft_skip_op(const char *s)
{
	int	i;

	i = 0;
	ft_printf("sk.s[%d]=%c\n",i, s[i]);
	while (s[i] == '>' || s[i] == '<')
	{
		while (s[i] == '>' || s[i] == '<')
			++i;
		while (ft_isspace(s[i]) && s[i])
			++i;
		while (!ft_isspace(s[i]) && s[i]
				&& s[i] != '>' && s[i] != '<' && s[i] != '|')
			++i;
		while (ft_isspace(s[i]) && s[i])
			++i;
		ft_printf("SK.s[%d]=%c\n",i,s[i]);
	}
	return (i);
}

// len of word + spaces before & after, if "    ls  la " will return 8
// stops if finds >, <, |
int	ft_strlen_sp(const char	*s, int flag)
{
	int	i;

	i = 0;
	while (ft_isspace(s[i]) && s[i])
		++i;
	while (!ft_isspace(s[i]) && s[i])
	{
		if (flag == 0 && (s[i] == '>' || s[i] == '<' || s[i] == '|'))
			break ;
		if (flag == 1 && s[i] == '|')
			break ;
		if (flag == 2 && (s[i] == '>' || s[i] == '<' || s[i] == '|'))
			break ;
		++i;
	}
	if (flag == 2 && (s[i] == '>' || s[i] == '<'))
	{
		ft_printf("1.i=%d,%c,\n",i,s[i]);
		i += ft_skip_op(s + i);
		ft_printf("2.i=%d,%c,\n",i,s[i]);
	}
	while (ft_isspace(s[i]) && s[i])
		++i;
	if (flag == 2 && (s[i] == '>' || s[i] == '<'))
	{
		ft_printf("3.i=%d,%c,\n",i,s[i]);
		i += ft_skip_op(s + i);
		ft_printf("4.i=%d,%c,\n",i,s[i]);
	}
	ft_printf("len.s=|%s|,i=%d\n",s,i);
	return (i);
}

int	ft_count_args(const char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] && s[i] != '|')
	{
		if (!ft_isspace(s[i]) && s[i] != '>' && s[i] != '<'
				&& (ft_isspace(s[i + 1]) || s[i + 1] == '\0'
				|| s[i + 1] == '>' || s[i + 1] == '<' || s[i + 1] == '|'))
		{
			++count;
//			ft_printf("s_counted=|%s|\n", s+i);
		}
		if (s[i] == '>' || s[i] == '<')
		{
//			ft_printf("s_1<>=|%s|\n", s+i);
			while (s[i] == '>' || s[i] == '<' || ft_isspace(s[i]))
				++i;
			while ((!ft_isspace(s[i])
					&& s[i] != '>' && s[i] != '<' && s[i] != '|' && s[i] != '\0'))
				++i;
			while (ft_isspace(s[i]) && s[i])
				++i;
//			ft_printf("s_2<>=|%s|\n", s+i);
		}
		else
			++i;
//		ft_printf("s_EOL=|%s|\n", s+i);
	}
	//ft_printf("s=|%s|\n", s+i);
	//ft_printf("s[%d]=%c,s[%d]=%c,c=%d\n",i,s[i],i+1,s[i+1],count);
	ft_printf("END:%d\n",count);
	return (count);
}

int	ft_strlen_op(t_ad *ad, const char *s)
{
	int		i;
	char	c;

	i = 0;
	c = s[0];
	while (s[i] == '>' || s[i] == '<')
	{
		if (s[i] != c)
			my_exit(ad, write(2, "Error: Reverse redirection operator\n", 36));
		++i;
	}
	if (i > 2)
		my_exit(ad, write(2, "Error: Too long redirection operator\n", 37));
	return (i);
}
