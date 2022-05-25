/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:23:14 by krioja            #+#    #+#             */
/*   Updated: 2022/05/25 18:07:11 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return len of word + spaces before and after, e.g. s = "    ls  la " will return 8
static int	ft_strlen_sp(const char	*s)
{
	int	i;

	i = 0;
	while (ft_isspace(s[i]) && s[i])
		++i;
	while (!ft_isspace(s[i]) && s[i])
		++i;
	while (ft_isspace(s[i]) && s[i])
	{
		++i;
//		ft_printf("ft_isspace(s[i])=%d, s[i=%d]=%d\n",ft_isspace(s[i]),i,s[i]);
	}
//	ft_printf("i = %d\n", i);
	return (i);
}

static int	ft_count_args(const char *s)
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

// strtrim(substr) > source of leaks??
static int	populate_pa(t_ad *ad, const char *l)
{
	int	n;
	
	n = 0;
	while (*l)
	{
		if (*l == '>' || *l == '<')
		{
			l += ft_strlen_sp(l);
			l += ft_strlen_sp(l);
		}
		else if (*l == '|')
			++l;
		else
		{
			if (!ad->pa)
				ad->pa = pa_lstnew(ad->pa);
			else
			{
				pa_lstadd_back(&ad->pa, pa_lstnew(ad->pa));
				pa_lst_fst_or_lst(&ad->pa, 1);
			}
			ad->pa->cmd = ft_strtrim(ft_substr(l, 0, ft_strlen_sp(l)), " ");
			if (ad->pa->cmd == NULL)
				return (1);
			l += ft_strlen_sp(l);
			ad->pa->args = malloc(sizeof(char *) * ft_count_args(l) + 1);
			while (*l != '|' && *l != '>' && *l != '<' && *l)
			{
				ad->pa->args[n] = ft_strtrim(ft_substr(l, 0, ft_strlen_sp(l)), " ");
				if (ad->pa->args[n] == NULL)
					return (2);
				l += ft_strlen_sp(l);
				++n;
			}
			ad->pa->args[n] = NULL;
			n = 0;
		}
	}
	pa_lst_fst_or_lst(&ad->pa, 0);
	n = 0;
	while (ad->pa)
	{
		ft_printf("ad.pa.cmd=|%s|\n",ad->pa->cmd);
		ft_printf("ad.pa.path=|%s|\n",ad->pa->path);
		while (ad->pa->args[n++])
			ft_printf("ad.pa.args[%d]=|%s|\n",n - 1,ad->pa->args[n - 1]);
		ad->pa = ad->pa->next;
		n = 0;
	}
	return (0);
}
// to put before return (0) to check all redir structs

static int	populate_redir(t_ad *ad, const char *l)
{
	while (*l)
	{
		if (*l == '>' || *l == '<')
		{
			if (!ad->redir)
				ad->redir = redir_lstnew(ad->redir);
			else
			{
				redir_lstadd_back(&ad->redir, redir_lstnew(ad->redir));
				redir_lst_fst_or_lst(&ad->redir, 1);
			}
			ad->redir->op = ft_strtrim(ft_substr(l, 0, ft_strlen_sp(l)), " ");
			if (ad->redir->op == NULL)
				return (1);
			l += ft_strlen_sp(l);
			ad->redir->file = ft_strtrim(ft_substr(l, 0, ft_strlen_sp(l)), " ");
			if (ad->redir->file == NULL)
				return (2);
			l += ft_strlen_sp(l);
		}
		else
			++l;
	}
	redir_lst_fst_or_lst(&ad->redir, 0);
	while (ad->redir)
	{
		ft_printf("ad.redir.op=|%s|\n",ad->redir->op);
		ft_printf("ad.redir.file=|%s|\n",ad->redir->file);
		ad->redir = ad->redir->next;
	}
	return (0);
}
// to put before return (0) to check all redir structs

int	ms_split(t_ad *ad)
{
	int	i;

	i = 0;
	if (!ad->line)
		return (1);
	if (populate_redir(ad, ft_strtrim(ad->line, " ")))
		return (2);
	if (populate_pa(ad, ft_strtrim(ad->line, " ")))
		return (3);
	return (0);
}
