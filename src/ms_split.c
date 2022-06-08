/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:23:14 by krioja            #+#    #+#             */
/*   Updated: 2022/06/08 17:29:44 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	populate_pa2(t_ad *ad, const char *l)
{
	int	n;
	int	ret;

	ft_printf(":O l=|%s|\n",l);
	n = 0;
	ret = 0;
/*	if (!ad->pa)
		ad->pa = pa_lstnew(ad->pa);
	else
		pa_lstadd_next(&ad->pa, pa_lstnew(ad->pa));*/
	ad->pa->cmd = ft_strtrim(ft_substr(l, 0, ft_strlen_sp(l, 0)), " ");
	if (ad->pa->cmd == NULL)
		my_exit(ad, write(2, "Error: Malloc (ad->pa->cmd)\n", 28));
	ad->pa->args = malloc(sizeof(char *) * (ft_count_args(l) + 1));
	while (*l != '|' && *l)
	{
		ad->pa->args[n] = ft_strtrim(ft_substr(l, 0, ft_strlen_sp(l, 0)), " ");
		if (ad->pa->args[n] == NULL)
			my_exit(ad, write(2, "Error: Malloc (ad->pa->args)\n", 29));
		ft_printf(":) arg[%d]=|%s|\n", n, ad->pa->args[n]);
		ret += ft_strlen_sp(l, 0);
		l += ft_strlen_sp(l, 0);
		++n;
	}
	ad->pa->args[n] = NULL;
	ft_printf(":D l=|%s|, ret=%d\n",l, ret);
	return (ret);
}

static int	add_redir(t_ad *ad, const char *l)
{
	int	ret;

	ret = 0;
	ret += ft_strlen_op(ad, l);	
	ret += ft_strlen_sp(l + ret, 0);
/*	if (!ad->pa)
		ad->pa = pa_lstnew(NULL);*/
	if (!ad->pa->redir)
		ad->pa->redir = redir_lstnew(ad->pa->redir);
	else
		redir_lstadd_next(&ad->pa->redir, redir_lstnew(ad->pa->redir));
	ad->pa->redir = ad->redir;
	ft_printf(":) PA redir op=|%s|\n", ad->pa->redir->op);
	ft_printf(":) PA redir file=|%s|\n", ad->pa->redir->file);
	ad->redir = ad->redir->next;
	ft_printf(":D l=|%s|, ret=%d\n",l, ret);
	return (ret);
}

static int	populate_pa(t_ad *ad, const char *l)
{
	int	n;

	n = 0;
	redir_lst_fst_or_lst(&ad->redir, 0);
	ad->pa = pa_lstnew(NULL);
	while (*l)
	{
		if (*l == '>' || *l == '<')
			l += add_redir(ad, l);
		else if (*l == '|')
		{
			++l;
			pa_lstadd_next(&ad->pa, pa_lstnew(ad->pa));
		}
		else
			l += populate_pa2(ad, l);
	}
	if (ad->pa->prev != NULL)
	{
		ft_printf("YOOOO\n");
		pa_lst_fst_or_lst(&ad->pa, 0);
	}
	ad->pa->redir->next = NULL;
	n = 0;
//	pa_lst_fst_or_lst(&ad->pa, 0);
	while (ad->pa)
	{
		ft_printf("--ad.pa.cmd=|%s|\n", ad->pa->cmd);
		ft_printf("ad.pa.path=|%s|\n", ad->pa->path);
		while (ad->pa->args[n])
		{
			ft_printf("ad.pa.args[%d]=|%s|\n", n, ad->pa->args[n]);
			++n;
		}
		redir_lst_fst_or_lst(&ad->pa->redir, 0);
		while (ad->pa->redir)
		{
			ft_printf("ad.pa.redir.op=|%s|\n", ad->pa->redir->op);
			ft_printf("ad.pa.redir.file=|%s|\n", ad->pa->redir->file);
			if (ad->pa->redir->next)
				ad->pa->redir = ad->pa->redir->next;
			else
				break;
		}
		ad->pa = ad->pa->next;
		n = 0;
	}

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
				redir_lstadd_next(&ad->redir, redir_lstnew(ad->redir));
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
		if (ad->redir->next)
			ad->redir = ad->redir->next;
		else
			break;
	}
	return (0);
}
/* to put before return (0) to check all redir structs
	while (ad->redir)
	{
		ft_printf("ad.redir.op=|%s|\n", ad->redir->op);
		ft_printf("ad.redir.file=|%s|\n", ad->redir->file);
		ad->redir = ad->redir->next;
	}
*/

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
