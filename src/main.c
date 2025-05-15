<<<<<<< HEAD
# include <stdio.h> //printf, readline, perror
# include <readline/readline.h> //readline, rl_*
# include <readline/history.h> //readline, rl_*
# include <stdlib.h> //malloc, free, exit, ttyslot, getenv
# include <unistd.h> //write, access, read, close, fork, getcwd, chdir, *stat, unlink, execve, dup*, pipe, isatty, ttyname, ttyslot, tcsetattr, tcgetattr
# include <sys/types.h> //open, wait*, kill, *stat, opendir, closedir
# include <sys/stat.h> //open, stat
# include <fcntl.h> //open
# include <sys/wait.h> //wait*
# include <signal.h> //signal, kill
# include <dirent.h> //*dir
# include <string.h> //strerror
# include <errno.h> //perror
# include <sys/ioctl.h> //ioctl
# include <termios.h> //tcsetattr, tcgetattr
# include <curses.h> //tgetent, tgetflag, tgetnum,tgetstr, tgoto, tputs
# include <term.h> //getent, tgetflag, tgetnum, tgetstr, tgoto, tputs

# include "../libft/libft.h"

int main(int ac, char **av, char **env)
{
	t_data	*data;

	while (1)
	{
		data->prompt_line = readline("minishell > ");
		if (data->prompt_line)
		{
			add_history(data->prompt_line);
			if (!parsing(data))
			{
				free();
				return (1);
			}
			if (!execution(data))
			{
				free();
				return (1);
			}
		}
	}
	return (0)
=======
# include "../header/minishell.h"

int main(int ac, char **av, char **env)
{
    t_data      *data;
    t_parsing   *parsing;

    data = malloc(sizeof(t_data));
    parsing = malloc(sizeof(t_parsing));
    if (!data || !parsing)
        return(ALL_OK);
    if (!struct_init(data, parsing, env))
        return(free_all(data, parsing));
    while (1)
    {
        parsing->prompt = readline("minishell > ");
        if (parsing->prompt)
		{
			add_history(parsing->prompt);
			if (!parser(data, parsing))
            {
                free_all(data, parsing);
                return (1);
            }
            if (!execution(data))
            {
                free_data(data);
                return (1);
            }
		}
    }
    return (0);
>>>>>>> ea3aff8c72e20c53410e20185f42908e47c4cb08
}
