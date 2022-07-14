/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:23:14 by krioja            #+#    #+#             */
/*   Updated: 2022/07/06 18:39:40 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	populate_redir(t_ad *ad, const char *l)
{
	int	ret;

	ret = 0;
	while (*(l + ret) == ' ')
		ret++;
	while (*(l + ret) == '>' || *(l + ret) == '<')
	{
		if (!ad->pa->redir)
			ad->pa->redir = redir_lstnew(NULL);
		else
			redir_lstadd_next(&ad->pa->redir, redir_lstnew(ad->pa->redir));
		ad->pa->redir->op = ft_strtrim_f(
				ft_substr(l + ret, 0, ft_strlen_op(l + ret)), " ");
		ret += ft_strlen_op(l + ret);
		ad->pa->redir->file = ft_strtrim_f(
				ft_substr(l + ret, 0, ft_strlen_sp(l + ret, 0)), " ");
		ret += ft_strlen_sp(l + ret, 0);
	}
	return (ret);
}

static void	check_special_char(t_ad *ad, char *l, int *ret, int *n)
{
	while (*(l + (*ret)) == ' ')
		(*ret)++;
	if (*(l + *ret))
	{
		if (*(l + *ret) == '\'')
		{
			ad->pa->args[*n] = ft_substr(l + *ret, 0,
					pos_n_char(l + *ret, 2, '\''));
			*ret += pos_n_char(l + *ret, 2, '\'');
		}
		else if (*(l + *ret) == '"')
		{
			ad->pa->args[*n] = ft_substr(l + *ret, 0,
					pos_n_char(l + *ret, 2, '"'));
			*ret += pos_n_char(l + *ret, 2, '"');
		}
		else
		{
			ad->pa->args[*n] = ft_strtrim_f(ft_substr(l + *ret, 0,
						ft_strlen_sp(l + *ret, 0)), " ");
			*ret += ft_strlen_sp(l + *ret, 0);
		}
	}
	*n = *n + 1;
	*ret += populate_redir(ad, l + (*ret));
}

static int	populate_pa(t_ad *ad, char *l, int *pop)
{
	int	n;
	int	ret;

	n = 0;
	ret = populate_redir(ad, l);
	if (ret < 0)
	{
		*pop = -1;
		write(2, REDIR_MSG, ft_strlen(REDIR_MSG));
		return (-1);
	}
	ad->pa->cmd = ft_strtrim_f(ft_substr(l + ret, 0,
				ft_strlen_sp(l + ret, 0)), " ");
	if (is_builtins(ad))
		ad->pa->is_blt = 1;
	if (ft_count_args(l) == -1)
	{
		*pop = -1;
		return (-1);
	}
	ad->pa->args = malloc(sizeof(char *) * (ft_count_args(l) + 1));
	while ((*(l + ret) != '|' && *(l + ret)))
		check_special_char(ad, l, &ret, &n);
	ad->pa->args[n] = NULL;
	return (ret);
}

static int	parse_line(t_ad *ad, char *l)
{
	char	*tmp;
	int		pop;

	ad->pa = pa_lstnew(NULL);
	ad->pa_head = ad->pa;
	tmp = l;
	pop = 0;
	while (*l)
	{
		l += populate_pa(ad, l, &pop);
		if (pop < 0)
			return (1);
		if (*l == '|')
		{
			++l;
			while (ft_isspace(*l) && *l)
				++l;
			pa_lstadd_next(&ad->pa, pa_lstnew(ad->pa));
		}
	}
	free(tmp);
	return (0);
}

int	ms_split(t_ad *ad)
{
	char	*tmp;

	if (!ad->line)
		return (1);
	tmp = ft_strtrim(ad->line, " \t\n\f\r\v");
	if (parse_line(ad, tmp))
	{
		free(tmp);
		return (3);
	}
	trim_quote(ad);
	return (0);
}
