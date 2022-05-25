/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:23:14 by krioja            #+#    #+#             */
/*   Updated: 2022/05/25 10:23:31 by krioja           ###   ########.fr       */
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
	while (s[i] && !ft_isspace(s[i]))
		++i;
	while (ft_isspace(s[i]) && s[i])
		++i;
	return (i);
}

//static int	ft_count_args(const char *s)
//{
//	int	count;
//	int	i;
//
//	count = 0;
//	i = 0;
//	while (ft_isspace(s[i]))
//		++i;
//	while (s[i] != '|' && s[i] != '>' && s[i] != '<' && s[i])
//	{
//		if (!ft_isspace(s[i]) && (ft_isspace(s[i + 1]) || s[i + 1] == '\0'))
//			++count;
//		++i;
//	}
//	return (count);
//}

// strtrim(substr) > source of leaks??
//static int	populate_pa(t_ad *ad)
//{
//	int	n;
//	
//	n = 0;
//	ad->pa = pa_lstnew(ad->pa);
//	ad->pa->cmd = ft_strtrim(ft_substr(s, 0, ft_strlen_sp(s)), " ");
//	if (ad->pa->cmd == NULL)
//		return (3);
//	s += ft_strlen_sp(s);
//	ad->pa->args = malloc(sizeof(char *) * ft_count_args(s) + 1);
//	while (*s != '|' && *s)
//	{
//			ft_printf("words=%d\n",*words);
//			ft_printf("s=|%s|\n",s);
//			ft_printf("pa.cmd=|%s|\n",ad->pa->cmd);
//			ft_printf("args=%d\n",ft_count_args(s));
//		ad->pa->args[n] = ft_strtrim(ft_substr(s, 0, ft_strlen_sp(s)), " ");
//			ft_printf("pa.args[%d]=|%s|\n",n, ad->pa->args[n]);
//		if (ad->pa->args[n] == NULL)
//			return (4);
//		s += ft_strlen_sp(s);
//		++n;
//			//ft_printf("pa.args[1]=|%s|\n",ad->pa->args[1]);
//	}
//	ft_printf("-------------pop finish\n");
//	return (0);
//}

// add next
static int	populate_redir(t_ad *ad, const char *l)
{
	while (*l)
	{
		if (*l == '>' || *l == '<')
		{
			if (!ad->redir)
				ad->redir = redir_lstnew(ad->redir); // comment faire pour pointer vers le prev?
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
			ft_printf("ad.redir.op=|%s|\n",ad->redir->op);
			ft_printf("ad.redir.file=|%s|\n",ad->redir->file);
		}
		else
			++l;
		ft_printf("l=|%s|\n", l);
	}
	// this goes to last, and prints all prevs
	redir_lst_fst_or_lst(&ad->redir, 0);
	while (ad->redir)
	{
//		if (ad->redir->next == NULL)
//			break;
		ft_printf("ad.redir.op=|%s|\n",ad->redir->op);
		ft_printf("ad.redir.file=|%s|\n",ad->redir->file);
		ad->redir = ad->redir->next;
	}
	return (0);
}

int	ms_split(t_ad *ad)
{
	int	i;

	i = 0;
	if (!ad->line)
		return (1);
	if (populate_redir(ad, ft_strtrim(ad->line, " ")))
		return (2) ;
//	if (populate_lsts(ad))
//		return (3) ;
	return (0);
}
