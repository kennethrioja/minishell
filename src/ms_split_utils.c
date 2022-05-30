/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:29:34 by krioja            #+#    #+#             */
/*   Updated: 2022/05/30 14:43:52 by krioja           ###   ########.fr       */
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
		++i;
	}
	while (ft_isspace(s[i]) && s[i])
		++i;
	return (i);
}

int	ft_count_args(const char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (ft_isspace(s[i]))
		++i;
	while (s[i] != '|' && s[i] != '>' && s[i] != '<' && s[i])
	{
		if (!ft_isspace(s[i]) && (ft_isspace(s[i + 1]) || s[i + 1] == '\0'))
			++count;
		++i;
	}
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
