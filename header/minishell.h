#ifndef MINISHELL_H
# define MINISHELL_H

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

/////////////////////////////////////////// enum ////////////////////////////////////////



typedef enum	e_error
{
	ALL_OK,
	ERR_CREAT,
	ERR_ID,
	ERR_EXEC,
	ERR_PIPE,
	ERR_RAFT,
	ERR_MALLOC
} t_error;

typedef enum	e_rafter
{
	NO_RAFTERS,
	SIMPLE_LEFT,
	DOUBLE_LEFT,
	SIMPLE_RIGHT,
	DOUBLE_RIGHT
} t_rafter;

/////////////////////////////////////// structures //////////////////////////////////////

typedef struct	s_env
{
	struct s_env	*next;
	char			*line;
} t_env;

typedef struct	s_token
{
	struct s_token	*next;
	char			**cmd;
	int				redirection[2];
	char			*io[2];
} t_token;

typedef struct	s_data
{
	t_env	*ls_env;
	t_token	*ls_token;
	t_env	*env_head;
	t_token	*token_head;
	int		pipe_nbr;
} t_data;

typedef struct	s_parsing
{
	int		p_index;
	int		word_length;
	char	skip;
	char	*prompt;
	char	**prompt_tab;
	bool	dollar;
	bool	simple_quote;
	bool	double_quote;
	t_data	*data;
} t_parsing;

//////////////////////////////////////// functions //////////////////////////////////////

int		struct_init(t_data *data, t_parsing *parsing, char **env);
char	*ft_cutstr(char const *s, unsigned int start);
char	**split_pipe_smart(char const *s, char c);
int		skip_under_quote(const char *str, size_t i);
int		parser(t_data *data, t_parsing *parsing);

/*EXEC*/
/*execution.c*/
int		execution(t_data *data);
/*command.c*/
char	*find_cmd(char **env, char *cmd);
/*utils_exec.c*/
char	*free_tab(char **table);
char	*ft_strtrim_improved(char *s1, char const *set);
int		tablen(char **table);
int		wait_for_pid(t_token *token, pid_t *pid);
char	**get_env_in_tab(t_env *node_env);
/*BUILTINS*/
int		cmd_is_builtin(char *path_cmd);
void	exec_homemade_builtin(t_data *data, int io_fd[2], char *path_cmd, int previous_output);

#endif
