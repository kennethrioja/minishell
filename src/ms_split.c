/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:23:14 by krioja            #+#    #+#             */
/*   Updated: 2022/06/01 19:19:00 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	populate_pa2(t_ad *ad, const char *l)
{
	int	n;
	int	ret;

	n = 0;
	ret = 0;
	if (!ad->pa)
		ad->pa = pa_lstnew(ad->pa);
	else
		pa_lstadd_back(&ad->pa, pa_lstnew(ad->pa));
	ad->pa->cmd = ft_strtrim(ft_substr(l, 0, ft_strlen_sp(l, 0)), " ");
	if (ad->pa->cmd == NULL)
		my_exit(ad, write(2, "Error: Malloc (ad->pa->cmd)\n", 28));
	ad->pa->args = malloc(sizeof(char *) * (ft_count_args(l) + 1));
	while (*l != '|' && *l)
	{
		ad->pa->args[n] = ft_strtrim(ft_substr(l, 0, ft_strlen_sp(l, 0)), " ");
		if (ad->pa->args[n] == NULL)
			my_exit(ad, write(2, "Error: Malloc (ad->pa->args)\n", 29));
		ret += ft_strlen_sp(l, 2);
		l += ft_strlen_sp(l, 2);
		++n;
	}
	ad->pa->args[n] = NULL;
	return (ret);
}

static int	populate_pa(t_ad *ad, const char *l)
{
//	int	n;

	while (*l)
	{
		if (*l == '>' || *l == '<')
		{
			l += ft_strlen_op(ad, l);
			l += ft_strlen_sp(l, 0);
		}
		else if (*l == '|')
			++l;
		else
			l += populate_pa2(ad, l);
	}
	pa_lst_fst_or_lst(&ad->pa, 0);
//	n = 0;
//	while (ad->pa)
//	{
//		ft_printf("--ad.pa.cmd=|%s|\n", ad->pa->cmd);
//		ft_printf("ad.pa.path=|%s|\n", ad->pa->path);
//		while (ad->pa->args[n++])
//			ft_printf("ad.pa.args[%d]=|%s|\n", n - 1, ad->pa->args[n - 1]);
//		ad->pa = ad->pa->next;
//		n = 0;
//	}
	return (0);
}
/* to put before return (0) to check all redir structs
	pa_lst_fst_or_lst(&ad->pa, 0);
	n = 0;
	while (ad->pa)
	{
		ft_printf("ad.pa.cmd=|%s|\n", ad->pa->cmd);
		ft_printf("ad.pa.path=|%s|\n", ad->pa->path);
		while (ad->pa->args[n++])
			ft_printf("ad.pa.args[%d]=|%s|\n", n - 1, ad->pa->args[n - 1]);
		ad->pa = ad->pa->next;
		n = 0;
	}
*/

static int	populate_redir(t_ad *ad, const char *l)
{
	while (*l)
	{
		if (*l == '>' || *l == '<')
		{
			if (!ad->redir)
				ad->redir = redir_lstnew(ad->redir);
			else
				redir_lstadd_back(&ad->redir, redir_lstnew(ad->redir));
			ad->redir->op = ft_strtrim(
					ft_substr(l, 0, ft_strlen_op(ad, l)), " ");
			if (ad->redir->op == NULL)
				my_exit(ad, write(2, "Error: Malloc (ad->redir->op)\n", 30));
			l += ft_strlen_op(ad, l);
			ad->redir->file = ft_strtrim(
					ft_substr(l, 0, ft_strlen_sp(l, 0)), " ");
			if (ad->redir->file == NULL)
				my_exit(ad, write(2, "Error: Malloc (ad->redir->file)\n", 32));
			if (!ad->redir->file[0])
				my_exit(ad, write(2, "Error: Redir file not specified\n", 32));
			l += ft_strlen_sp(l, 0);
		}
		else
			++l;
	}
	redir_lst_fst_or_lst(&ad->redir, 0);
	while (ad->redir)
	{
		ft_printf("-ad.redir.op=|%s|\n", ad->redir->op);
		ft_printf("ad.redir.file=|%s|\n", ad->redir->file);
		ad->redir = ad->redir->next;
	}
	return (0);
}
/* to put before return (0) to check all redir structs
	redir_lst_fst_or_lst(&ad->redir, 0);
	while (ad->redir)
	{
		ft_printf("ad.redir.op=|%s|\n", ad->redir->op);
		ft_printf("ad.redir.file=|%s|\n", ad->redir->file);
		ad->redir = ad->redir->next;
	}
*/

int	ms_split(t_ad *ad)
{
//	int	i;
//
//	i = 0;
	if (!ad->line)
		return (1);
	if (populate_redir(ad, ft_strtrim(ad->line, " ")))
		return (2);
	if (populate_pa(ad, ft_strtrim(ad->line, " ")))
		return (3);
	return (0);
}
