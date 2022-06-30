/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:14:04 by krioja            #+#    #+#             */
/*   Updated: 2022/06/28 13:31:40 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_heredoc(t_ad *ad)
{
	char	*tmp;
	int		fd[2];

	if (!ft_strcmp(ad->pa->redir->op, "<<"))
	{
		if (pipe(fd) == -1)
			my_exit(ad, write(2, "Error: pipe for <<\n", 19));
		while (1)
		{
			tmp = readline("> ");
			if (!ft_strcmp(ad->pa->redir->file, tmp))
				break ;
			write(fd[1], tmp, ft_strlen(tmp));
			write(fd[1], "\n", 1);
			if (tmp)
				free(tmp);
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		free(tmp);
	}
}

static void	redir_infile(t_ad *ad)
{
	int	infile;

	if (!ft_strcmp(ad->pa->redir->op, "<"))
	{
		infile = open(ad->pa->redir->file, O_RDWR);
		if (infile == -1)
			my_exit(ad, write(2, "adsh: ", 6)
				+ write(2, ad->pa->redir->file, ft_strlen(ad->pa->redir->file))
				+ write(2, ": No such file or directory\n", 28));
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
}

static void	redir_outfile(t_ad *ad)
{
	int	outfile;
//	int	tmp;

	if (!ft_strncmp(ad->pa->redir->op, ">", 1))
	{
//		tmp = dup(STDOUT_FILENO);
		if (!ft_strcmp(ad->pa->redir->op, ">>"))
			outfile = open(ad->pa->redir->file,
					O_RDWR | O_APPEND | O_CREAT, 0644);
		else
			outfile = open(ad->pa->redir->file, O_RDWR | O_CREAT, 0644);
		if (outfile == -1)
		{
			my_exit(ad, write(2, "Error: outfile\n", 15));
		}
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
//		dup2(tmp, STDOUT_FILENO);
//		close(tmp);
	}
}

void	ms_exec_redir(t_ad *ad)
{
	if (ad->pa->redir)
	{
		redir_lst_fst_or_lst(&ad->pa->redir, 0);
		while (ad->pa->redir)
		{
			redir_outfile(ad);
			redir_infile(ad);
			redir_heredoc(ad);
			if (ad->pa->redir->next)
				ad->pa->redir = ad->pa->redir->next;
			else
				break ;
		}
	}
}
