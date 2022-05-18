/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:59:59 by krioja            #+#    #+#             */
/*   Updated: 2022/05/18 15:42:31 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**add_prefix(char ***params, char **path, char *prefix)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (prefix[1] == 'b')
	{
		*path = malloc(sizeof(char) * (word_length((*params)[0], 0) + 5 + 1));
		while (prefix[++i])
			(*path)[i] = prefix[i];
		while ((*params)[0][++j])
			(*path)[i++] = (*params)[0][j];
		(*path)[i] = '\0';
		return (path);
	}
	*path = malloc(sizeof(char) * (word_length((*params)[0], 0) + 9 + 1));
	while (prefix[++i])
		(*path)[i] = prefix[i];
	while ((*params)[0][++j])
		(*path)[i++] = (*params)[0][j];
	(*path)[i] = '\0';
	return (path);
}

static void	get_path(char ***params, char **path)
{
	path = add_prefix(params, path, "/bin/");
	if (access(*path, F_OK) == -1)
	{
		free(*path);
		path = add_prefix(params, path, "/usr/bin/");
		if (access(*path, F_OK) == -1)
		{
			free(*path);
			perror("Error (path)");
		}
	}
}

static void	get_params(char **env, t_ad *ad)
{
	int	i;

	i = -1;
	ms_lstnew(ad->pp);
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
				(*params)[n] = malloc(sizeof(char) * word_length(argvx, n) + 1);
			}
			(*params)[n][j] = argvx[i];
			++j;
		}
	}
	(*params)[++n] = NULL;
}

void	get_pp(char **env, t_ad *ad)
{
	get_params(env, ad);
	get_path(env, ad);
}
