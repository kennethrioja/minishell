/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krioja <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:09:16 by krioja            #+#    #+#             */
/*   Updated: 2022/05/25 18:19:32 by krioja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// 42 libraries
# include "../src/ft/ft_printf/ft_printf.h"
# include "../src/ft/libft/libft.h"

// .h libraries
# include <curses.h>				
// tgetent(), tgetflag(), tgetnum(), tgetstr(), tgoto(), tputs()
# include <dirent.h>				
// opendir(), readdir(), closedir()
# include <fcntl.h>					
// open()
# include <readline/readline.h>		
// readline()
# include <readline/history.h>		
// readline()
# include <signal.h>				
// signal(), sigaction(), sigemptyset(), sigaddset(), kill()
# include <sys/ioctl.h>				
// ioctl()
# include <sys/stat.h>				
// stat(), lstat(), fstat()
# include <sys/types.h>				
// read()
# include <sys/uio.h>				
// read()
# include <sys/wait.h>				
// wait(), waitpid(), wait3(), wait4()
# include <stdio.h>					
// readline(), printf(), strerror(), perror()
# include <stdlib.h>				
// malloc(), free(), exit(), getenv(), 
# include <term.h>					
// tgetent(), tgetflag(), tgetnum(), tgetstr(), tgoto(), tputs()
# include <termios.h>				
// tcsetattr(), tcgetattr()
# include <unistd.h>				
// write(), access(), read(), close(), fork(), getcwd(), chdir(),
// unlink(), execve(), dup(), dup2(), pipe(), isatty(), ttyname(), ttyslot()

// typedef, struct & vars

typedef struct s_redir
{
	char			*op;
	char			*file;
	struct s_redir	*prev;
	struct s_redir	*next;
}					t_redir;

typedef struct s_pa
{
	char			*cmd;
	char			*path;
	char			**args;
	struct s_pa		*prev;
	struct s_pa		*next;
//	t_redir			*redir;
}					t_pa;

typedef struct s_ad
{
	char			*line;
	t_redir			*redir;
	t_pa			*pa;
}					t_ad;

// minishell functions

//* get_line.c
int		get_line(t_ad *ad);

//* ms_utils_split.c
int		ms_split(t_ad *ad);

//* lst_redir_utils.c
t_redir	*redir_lstnew(struct s_redir *previous);
void	redir_lst_fst_or_lst(t_redir **redir, int flag);
void	redir_lstadd_back(t_redir **alst, t_redir *next);

//* lst_pa_utils.c
t_pa	*pa_lstnew(struct s_pa *previous);
void	pa_lst_fst_or_lst(t_pa **pa, int flag);
void	pa_lstadd_back(t_pa **alst, t_pa *next);

//* ms_utils.c

//* signal.c
void	sig_handler(int signum);
void	get_signal(void);

//* free_all.c
void	free_all(t_ad *ad);

#endif
