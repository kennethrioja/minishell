/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:32:31 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/05/30 13:27:14 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_ad *ad)
{
	t_node	*tmp;

	if (!ft_strcmp(ad->line, "export"))
	{
		tmp = ad->env_s;
		while (tmp)
		{
			// ft_printf("declare -x %s=\"%s\"\n", ad->env[i][0], ad->env[i][1]);
			ft_printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
	else
	{
//		ft_set_env(ad, );
		ft_printf("export: %s: No such file or directory\n", ad->line + 4);
	}
}

void	append_env(t_node **head_ref, char *key, char *value)
{
	t_node	*new_node;
	t_node	*last;

	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	if (*head_ref == NULL)
	{
		new_node->prev = NULL;
		*head_ref = new_node;
		return ;
	}
	last = *head_ref;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
	return ;
}

void	delete_env(t_node **head_ref, t_node *del)
{
	if (*head_ref == NULL || del == NULL)
		return ;
	if (*head_ref == del)
		*head_ref = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
	free(del);
	return ;
}

//void	ft_set_env(t_ad *ad, char *rule, char *str, int overwrite)
//{
//	int		i;
//	int		j;
//	char	*ruleeq;
//	char	**tmp;
//
//	j = -1;
//	while (ad->env[++j])
//	{
//		if (!ft_strncmp(ad->env[j], rule, ft_strlen(rule)))
//		{
//			if (overwrite)
//			{
//				free(ad->env[j]);
//				ruleeq = ft_strjoin(rule, "=");
//				ad->env[j] = ft_strjoin(ruleeq, str);
//			}
//		}
//		else
//		{
//			i = ft_arrlen(ad->env) + 1;
//			tmp = ft_calloc(i + 1, sizeof(ad->env));
//			j = 0;
//			while (j < i - 1)
//			{
//				tmp[j] = ft_strdup(ad->env[j]);
//				j++;
//			}
//			ruleeq = ft_strjoin(rule, "=");
//			ad->env[j] = ft_strjoin(ruleeq, str);
//			ad->env[j + 1] = NULL;
//		}
//	}
//}
