/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 15:42:53 by krioja            #+#    #+#             */
/*   Updated: 2022/05/18 17:50:19 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_op(t_ad *ad, int i)
{
	if (ad->line[i] == '>')
	{
		if (ad->line[i + 1] == '>')
			ad->
	}
}

void	get_redir(t_ad *ad)
{
	int	i;

	i = -1;
	if (has_op(ad))
	{
		ad->redir = malloc(sizeof(t_redir));
		while (ad->line[++i])
		{
			i = is_op(ad, i)

		}
}
