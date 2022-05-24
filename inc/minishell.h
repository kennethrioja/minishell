/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:09:16 by krioja            #+#    #+#             */
/*   Updated: 2022/05/24 13:46:45 by tpinto-m         ###   ########.fr       */
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

// macro

// * builtins
# define MS_ECHO "echo"
# define MS_CD "cd"
# define MS_PWD "pwd"
# define MS_EXPORT "export"
# define MS_UNSET "unset"
# define MS_ENV "env"
# define MS_EXIT "exit"

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

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
	char			**args;
	struct s_pa		*prev;
	struct s_pa		*next;
}					t_pa;

typedef struct s_ad
{
	char			*line;
	char			**env;
	t_redir			*redir;
	t_pa			*pa;
}					t_ad;

// minishell functions

//* get_line.c
int		get_line(t_ad *ad);
void	check_line(t_ad *ad);

//*	get_redir.c
void	get_redir(t_ad *ad);

//* get_pa.c
void	get_pa(char **env, t_ad *ad);

//* ms_utils.c
int		ft_strcmp(char *s1, char *s2);
int		ft_arrlen(char **arr);
int		ft_strlen_c(char *str, char c);

//* lst_utils.c
t_pa	*ms_lstnew(void *content);
t_pa	*ms_lstlast(t_pa *pa);
void	ms_lstadd_back(t_pa **pa, t_pa *panew);

//* signal.c
void	sig_handler(int signum);
void	get_signal(void);

//* free_all.c
void	free_all(t_ad *ad);

//* builtins

//** builtins/echo.c
void	ft_echo(t_ad *ad);

// ** builtins/pwd.c
void	ft_pwd(t_ad *ad);

// ** builtins/cd.c
void	ft_cd(t_ad *ad);

// ** builtins/env.c
void	ft_env(t_ad *ad);
void	init_env(t_ad *ad, char	**env);
void	ft_set_env(t_ad *ad, char *rule, char *str, int overwrite);

#endif
