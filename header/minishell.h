#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //printf, readline, perror
# include <readline/readline.h> //readline, rl_*
# include <readline/history.h> //readline, rl_*
# include <stdlib.h> //malloc, free, exit, ttyslot, getenv
# include <unistd.h> //write, access, read, close, fork, getcwd, chdir,
	//*stat, unlink, execve, dup*,
	//pipe, isatty, ttyname, ttyslot, tcsetattr, tcgetattr
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

/////////////////////////////////////////// enum

typedef enum e_error
{
	ERR_MALLOC = -42,
	ERR_PROMPT = -1,
	ALL_OK,
	ERR_CREAT,
	ERR_ID,
	ERR_EXEC,
	ERR_PIPE,
	ERR_RAFT,
	ERR_SYNTAXE
}	t_error;

typedef enum e_rafter
{
	DEFAULT = -1,
	EMPTY_RAFTER,
	SIMPLE_LEFT,
	DOUBLE_LEFT,
	SIMPLE_RIGHT,
	DOUBLE_RIGHT
}	t_rafter;

typedef enum e_err_exec
{
	NO_ERROR,
	ERROR_SYSTEM,
	ERROR_PROMPT,
}	t_err_exec;

/////////////////////////////////////// structures

typedef struct s_env
{
	struct s_env	*next;
	char			*line;
}	t_env;

typedef struct s_token
{
	struct s_token	*next;
	char			**cmd;
	t_rafter		io_redir[2];
	char			*io_value[2];
}	t_token;

typedef struct s_data
{
	t_env	*ls_env;
	t_token	*ls_token;
	int		pipe_nbr;
}	t_data;

typedef struct s_parsing
{
	int		pipe_seg;
	int		p_index;
	int		word_length;
	char	skip;
	char	*prompt;
	char	**prompt_tab;
	bool	dollar;
	bool	simple_quote;
	bool	double_quote;
	bool	outfile_issue;
	t_data	*data;
}	t_parsing;

//////////////////////////////////////// functions

/*EXEC*/
/*execution.c*/
int		execution(t_data *data);
int		redirect_and_exec(t_data *data, int *io_fd, char *path_cmd, char **env);
/*command.c*/
char	*find_cmd(char **env, char *cmd);
/*utils_exec.c*/
char	*ft_strtrim_improved(char *s1, char const *set);
int		tablen(char **table);
int		wait_for_pid(t_token *token, pid_t *pid);
char	**get_env_in_tab(t_env *node_env);
int		exec_single_cmd(t_data *data);
int		count_cmds(t_token *token);
/*clean.c*/
void	close_free_data_env_pids(t_data *data, int fd0, int fd1, pid_t *pids);
void	free_data_env(t_data *data);
void	close_all(int fd0, int fd1);
void	close_free_data_env(t_data *data, int fd0, int fd1);
void	close_free_array_str(int fd0, int fd1, char **env, char *path);
/*error_exec.c*/
void	msg_exit(char *message, int fd, int exit_value);
int	msg_return(char *message, int fd, int return_value);
int	perror_return(char *message, int return_value);
int	msg_return_close_all(int *fds, char *message, int fd, int return_value);
/*children.c*/
int	loop_children(t_data *data, t_token *current, pid_t *pids);
/*input_output.c*/
int	redirect_and_exec(t_data *data, int *io_fd, char *path_cmd, char **env);
int	get_input(char *io_value[2], t_rafter redirection[2], int previous_pipe);
int	get_output(char *io_value[2], t_rafter redirection[2], int pipe_output, int count_cmd);
/*BUILTINS*/
int		cmd_is_builtin(char *path_cmd);
int		exec_homemade_builtin(t_data *data);
int		var_cmp(char *s1, char *s2);
void	exec_echo(char **cmd);
int		exec_export(t_env *ls_env, char **cmds);
int		exec_pwd(void);
void	exec_env(t_env *ls_env);
void	exec_unset(t_env **ls_env, char **cmds);
int		exec_cd(char **cmd, t_env *list_env);
int		exec_exit(t_data *data, t_token *cmds, t_env *ls_env);

/*PARSING*/
/*parsing.c*/
void	ft_parsing(t_data *data, t_parsing *parsing, int *errcode);
/*prompt_check.c*/
int		prompt_check(char *prompt, t_parsing *parsing);
/*expand_var.c*/
void	quote_check(char c, t_parsing *parsing);
int		expand_var(t_data *data, t_parsing *parsing);
/*extract_token_without_quotes.c*/
char	*extract_token_without_quotes(char *str, t_parsing *parsing);
/*ft_coutpipe_utils.c*/
int	prompt_begins_with_a_pipe(const char *s, int *i, int *errcode);
int	parse_pipe_segments(char const *s, char c, int i);
/*manage_dollar*/
int		manage_dollar(t_data *data, t_parsing *parsing);
/*manage_dollar_utils*/
char	*find_var_name(t_parsing *parsing);
/*pip_segmentation.c*/
char	**pipe_segmentation(char const *s, char c, int *errcode);
/*skip_quote.c*/
int		skip_quote(const char *str, int *i);
/*tokenisation.c*/
int		tokenisation(t_data *data, t_parsing *parsing);
/*manage_quotes.c*/
int		manage_quotes(char c, t_parsing *parsing);
/*linked_list_token.c*/
t_token	*token_lstnew(void);
void	token_lstadd_back(t_token **lst, t_token *new);
/*cmd_token_utils.c*/
char	**split_whitespace_quotes(char const *s, char c, t_parsing *parsing);
/*cmd_token.c*/
char	*extract_clean_cmd(char *prompt);
/*rafter_token.c*/
int	manage_rafters(t_data *data, t_parsing *parsing, int *i, char *prompt);
/*manage_heredoc.c*/
int 	here_doc(char *eof);


/*UTILS*/
/*cutstr.c*/
char	*ft_cutstr(char const *s, unsigned int start);
/*print_err_message.c*/
int		err_message(t_error error);
/*debug_print.c*/
void	print_env(t_env *env);
void	print_prompt_tab(char **p_tab);
void	print_tokens(t_data *data);
/*free_minishell.c*/
void	free_all(t_parsing *parsing);
/*free_utils.c*/
char	*free_array(char **array);
void	free_env(t_env *env);
void	free_token(t_token *token);
/*ft_isspace.c*/
int		ft_isspace(char c);

/*MAIN*/
/*struct_init.c*/
int		struct_init(t_data *data, t_parsing *parsing);
int		env_init(char **env, t_data *data);

#endif
