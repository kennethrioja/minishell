/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:59:59 by krioja            #+#    #+#             */
/*   Updated: 2022/05/18 16:26:11 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**add_prefix(char ***args, char **path, char *prefix)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (prefix[1] == 'b')
	{
		*path = malloc(sizeof(char) * (word_length((*args)[0], 0) + 5 + 1));
		while (prefix[++i])
			(*path)[i] = prefix[i];
		while ((*args)[0][++j])
			(*path)[i++] = (*args)[0][j];
		(*path)[i] = '\0';
		return (path);
	}
	*path = malloc(sizeof(char) * (word_length((*args)[0], 0) + 9 + 1));
	while (prefix[++i])
		(*path)[i] = prefix[i];
	while ((*args)[0][++j])
		(*path)[i++] = (*args)[0][j];
	(*path)[i] = '\0';
	return (path);
}

static void	get_path(char ***args, char **path)
{
	path = add_prefix(args, path, "/bin/");
	if (access(*path, F_OK) == -1)
	{
		free(*path);
		path = add_prefix(args, path, "/usr/bin/");
		if (access(*path, F_OK) == -1)
		{
			free(*path);
			perror("Error (path)");
		}
	}
}

static void	get_args(char **env, t_ad *ad)
{
	int	i;

	i = -1;
	ms_lstnew(ad->pa);
	while (ad->line[++i])
	{
	//////////// il faut virer les redir de line en premier !!!	
	}


	while (argvx[++i])
	{
		if (!is_word(argvx[i]))
			++i;
		if (is_word(argvx[i]))
		{
			if (i == 0 || !is_word(argvx[i - 1]))
			{
				j = 0;
				++n;
				(*args)[n] = malloc(sizeof(char) * word_length(argvx, n) + 1);
			}
			(*args)[n][j] = argvx[i];
			++j;
		}
	}
	(*args)[++n] = NULL;
}

void	get_pa(char **env, t_ad *ad)
{
	get_args(env, ad);
	get_path(env, ad);
}
