/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:42:53 by krioja            #+#    #+#             */
/*   Updated: 2022/05/18 19:22:32 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	malloc_op(t_ad *ad, char c, int	n)
{
	int	i;

	i = -1
	if (n == 1 || n == 2)
	{
		ad->redir->op = malloc(sizeof(char) * n + 1);
		while (ad->redir->op[++i])
			ad->redir->op[i] = c;
	}
}

static int	check_op(t_ad *ad, int i)
{
	int	n;

	n = 0;
	while (ad->line[i] && ad->line[i] == '>')
	{
		++n;
		if (ad->line[i + 1] != '>' && get_op(ad, '>', n))
			return (i);
	}
	while (ad->line[i] && ad->line[i] == '<')
	{
		++n;
		if (ad->line[i + 1] != '<' && get_op(ad, '<', n))
			return (i);
	}
}

int	get_redir(t_ad *ad)
{
	int	i;

	i = -1;
	if (ft_strchr(ad->line, '>') || ft_strchr(ad->line, '<'))
	{
		ad->redir = malloc(sizeof(t_redir));
		while (ad->line[++i])
		{
			check_op(ad, i)
		}
	}
}
