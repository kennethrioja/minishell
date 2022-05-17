#ifndef MINISHELL_H
# define MINISHELL_H

// 42 libraries
# include "../src/ft_printf/ft_printf.h"
//# include "../ft_functions/libft/libft.h"
//# include "../ft_functions/get_next_line/get_next_line.h"

// .h libraries
# include <curses.h>				// tgetent(), tgetflag(), tgetnum(), tgetstr(), tgoto(), tputs()
# include <dirent.h>				// opendir(), readdir(), closedir()
# include <fcntl.h>					// open()
# include <readline/readline.h>		// readline()
# include <readline/history.h>		// readline()
# include <signal.h>				// signal(), sigaction(), sigemptyset(), sigaddset(), kill()
# include <sys/ioctl.h>				// ioctl()
# include <sys/stat.h>				// stat(), lstat(), fstat()
# include <sys/types.h>				// read()
# include <sys/uio.h>				// read()
# include <sys/wait.h>				// wait(), waitpid(), wait3(), wait4()
# include <stdio.h>					// readline(), printf(), strerror(), perror()
# include <stdlib.h>				// malloc(), free(), exit(), getenv(), 
# include <term.h>					// tgetent(), tgetflag(), tgetnum(), tgetstr(), tgoto(), tputs()
# include <termios.h>				// tcsetattr(), tcgetattr()
# include <unistd.h>				// write(), access(), read(), close(), fork(), getcwd(), chdir(), unlink(), execve(), dup(), dup2(), pipe(), isatty(), ttyname(), ttyslot()

// typedef, struct & vars

// minishell functions

void	sig_handler(int signum);
void	get_signal(void);

char	*get_line(void);

int		ft_strlen(char *str);
void	put_str(char *str);

#endif
