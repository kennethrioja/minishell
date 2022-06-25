/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:09:16 by krioja            #+#    #+#             */
/*   Updated: 2022/06/09 21:52:58 by krioja           ###   ########.fr       */
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

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

# define SUCCESS 0
# define GENERAL_ERR 1
# define PERMISSION_ERR 126
# define NOT_FOUND_ERR 127
# define EXIT_ERR 255
# define SIGNAL_ERR 128

# define PERMISSION_MSG "Permission denied"
# define NOT_FOUND_DIR_MSG "No such file or directory"
# define VALID_IDENTIFIER_MSG "Not a valid identifier"
# define NOT_FOUND_CMD_MSG "command not found"
# define EXIT_MSG "numeric argument required"
# define ARGS_MSG "too many arguments"

# define SHELL_NAME "adsh"

// typedef, struct & vars

int	g_status_exit;

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
	t_redir			*redir;
	struct s_pa		*prev;
	struct s_pa		*next;
}					t_pa;

typedef struct s_node
{
	char			*key;
	char			*value;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_ad
{
	char			*line;
	t_node			*env;
	t_redir			*redir;
	t_pa			*pa;
	t_pa			*pa_head;
}					t_ad;

// minishell functions

//* get_line.c
int		get_line(t_ad *ad);
void	check_line(t_ad *ad);

//* ms_split.c
int		ms_split(t_ad *ad);

//* ms_split_utils.c
int		ft_strlen_op(t_ad *ad, const char *s);
int		ft_count_args(const char *s);
int		ft_strlen_sp(const char	*s, int flag);
int		ft_skip_op(const char *s);

//* ms_split_redir_utils.c
t_redir	*redir_lstnew(struct s_redir *previous);
void	redir_lst_fst_or_lst(t_redir **redir, int flag);
void	redir_lstadd_next(t_redir **alst, t_redir *next);

//* ms_split_pa_utils.c
t_pa	*pa_lstnew(struct s_pa *previous);
void	pa_lst_fst_or_lst(t_pa **pa, int flag);
void	pa_lstadd_next(t_pa **alst, t_pa *next);

//* ms_utils.c
int		ft_strcmp(char *s1, char *s2);
size_t	ft_arrlen(char **arr);
size_t	ft_strlen_c(char *str, char c);
char	*ft_strtolower(char *str);
void	custom_err(t_ad *ad, int arg, char *str);

//* lst_utils.c
t_pa	*ms_lstnew(void *content);
t_pa	*ms_lstlast(t_pa *pa);
void	ms_lstadd_next(t_pa **pa, t_pa *panew);

//* signal.c
void	sig_handler(int signum);
void	handle_signal(void);

//* free_all.c
void	my_exit(t_ad *ad, int flag);
void	free_all(t_ad *ad);
void	free_cmd(t_ad *ad);

//* path.c
int		check_path(t_ad *ad);
void	exec_cmd(t_ad *ad, char *cmd);

//* dollar.c
void	check_dollar(t_ad *ad);

//* ms_pipex.c
int		ms_pipex(t_ad *ad);

//* builtins

//** builtins/echo.c
void	ft_echo(t_ad *ad);

// ** builtins/pwd.c
void	ft_pwd(void);

// ** builtins/cd.c
void	ft_cd(t_ad *ad);

// ** builtins/env.c
void	ft_env(t_ad *ad);
int		get_i_env(t_ad *ad, char *key);
t_node	*get_env(t_ad *ad, int i);
void	init(t_ad *ad, char	**env);
void	add_env(t_ad *ad, int arg, char *name, char *value);

// ** builtins/export.c
void	ft_export(t_ad *ad);
int		ft_isexport(const char *str);

// ** builtins/unset.c
void	ft_unset(t_ad *ad);
void	delete_t_node(t_node **head_ref, t_node *del);

// ** builtins/exit.c
void	ft_exit(t_ad *ad);

// ** builtins/cd.c
void	free_env(t_ad *ad);
int		count_t_node(t_node *node);
void	append_t_node(t_node **head_ref, char *key, char *value);
void	print_node(t_node	*node, int option);

#endif
