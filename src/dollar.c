/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 09:48:22 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/06/28 11:17:29 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO NORME it and CHANGE function !!
char	*ft_strreplace(char *s, const char *oldW, const char *newW)
{
	char	*result;
	int		i;
	int		cnt;
	int		new_wlen;
	int		old_wlen;

	cnt = 0;
	new_wlen = ft_strlen(newW);
	old_wlen = ft_strlen(oldW);
	i = -1;
	while (s[++i])
	{
		if (ft_strnstr(&s[i], oldW, ft_strlen(&s[i])))
		{
			cnt++;
			i += old_wlen - 1;
		}
	}
	result = (char *)malloc(i + cnt * (new_wlen - old_wlen) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (strstr(s, oldW) == s)
		{
			strcpy(&result[i], newW);
			i += new_wlen;
			s += old_wlen;
		}
		else
			result[i++] = *s++;
	}
	result[i] = '\0';
	return (result);
}

void	check_dollar(t_ad *ad)
{
	int	i;
	int	j;

	pa_lst_fst_or_lst(&ad->pa, 0);
	if (!ad->pa)
		return ;
	while (ad->pa)
	{
		i = -1;
		while (++i < (int)ft_arrlen(ad->pa->args))
		{
			if (ad->pa->args[i][0] != '\'')
			{
				j = -1;
				while (ad->pa->args[i][++j])
				{
					if (ad->pa->args[i][j] == '$')
					{
						if (ad->pa->args[i][j + 1] == '?')
							ad->pa->args[i] = ft_strreplace(ad->pa->args[i], "$?", ft_itoa(g_status_exit));
					}
				}
			}
			else
			{
				ad->pa->args[i] = ft_strtrim_f(ad->pa->args[i], "'");
			}
//			if (ad->pa->args[i][0] == '$' && ad->pa->args[i][1] != '?')
//			{
//				if (get_i_env(ad, ad->pa->args[i] + 1) != -1)
//				{
//					ad->pa->args[i] = get_env(ad, get_i_env(ad,
//								ad->pa->args[i] + 1))->value;
//				}
//			}
//			else if (!ft_strcmp(ad->pa->args[i], "$?"))
//				ad->pa->args[i] = ft_strdup(ft_itoa(g_status_exit));
		}
		ad->pa = ad->pa->next;
	}
	ad->pa = ad->pa_head;
}
