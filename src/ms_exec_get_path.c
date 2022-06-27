/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_get_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:45:17 by krioja            #+#    #+#             */
/*   Updated: 2022/06/20 14:36:38 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_lst_fst_or_lst(t_node **env, int flag)
{
	if (flag == 0)
	{
		while (*env)
		{
			if ((*env)->prev == NULL)
				break ;
			*env = (*env)->prev;
		}
	}
	else
	{
		while (*env)
		{
			if ((*env)->next == NULL)
				break ;
			*env = (*env)->next;
		}
	}
}

static int	add_prefix(t_ad *ad, const char *s, int n)
{
	char	**path;
	int		i;

	i = -1;
	env_lst_fst_or_lst(&ad->env, 0);
	while (ft_strncmp(ad->env->key, "PATH", 4))
		ad->env = ad->env->next;
	path = ft_split(ad->env->value, ':');
	ad->pa->path = ft_strjoin(path[n], "/");
	ad->pa->path = ft_strjoin(ad->pa->path, s);
	while (path[++i])
		free(path[i]);
	free(path);
	if (ad->pa->path == NULL)
		return (0);
	return (n + 1);
}

void	set_path(t_ad *ad)
{
	int	n;

	n = 0;
//	pa_lst_fst_or_lst(&ad->pa, 0);
//	while (ad->pa)
//	{
		while (access(ad->pa->path, F_OK) == -1)
		{
			if (ad->pa->path)
				free(ad->pa->path);
			n = add_prefix(ad, ad->pa->cmd, n);
			if (n == 0)
			{
				custom_err(ad, 0, NOT_FOUND_CMD_MSG);
				free_all(ad);
				return ;
			}
		}
//		if (ad->pa->next)
//			ad->pa = ad->pa->next;
//		else
//			break ;
//		n = 0;
//	}
}
