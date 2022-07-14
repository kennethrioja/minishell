/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:29:34 by krioja            #+#    #+#             */
/*   Updated: 2022/07/06 18:34:15 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_skip_op(const char *s)
{
	int	i;

	i = 0;
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
		i += ft_skip_op(s + i);
	while (ft_isspace(s[i]) && s[i])
		++i;
	if (flag == 2 && (s[i] == '>' || s[i] == '<'))
		i += ft_skip_op(s + i);
	return (i);
}

static int	skip_between_char(const char *s, int i, char c)
{
	if (s[i] == c)
	{
		i++;
		while (s[i])
		{
			i++;
			if (s[i] == c)
				return (i);
		}
		write(2, EVEN_MSG, ft_strlen(EVEN_MSG));
		return (-1);
	}
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
		i = skip_between_char(s, i, '\'');
		if (i == -1)
			return (-1);
		i = skip_between_char(s, i, '"');
		if (i == -1)
			return (-1);
		if (!ft_isspace(s[i]) && s[i] != '>' && s[i] != '<'
			&& (ft_isspace(s[i + 1]) || s[i + 1] == '\0'
				|| s[i + 1] == '>' || s[i + 1] == '<' || s[i + 1] == '|'))
			++count;
		if (s[i] == '>' || s[i] == '<')
			i += ft_skip_op(s + i);
		else
			++i;
	}
	return (count);
}

int	ft_strlen_op(const char *s)
{
	int		i;

	i = 0;
	while (s[i] == '>' || s[i] == '<')
	{
		++i;
	}
	return (i);
}
