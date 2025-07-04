# ifndef MINISHELL_H
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

# define MALLOC "Error: malloc failed\n"
# define NO_FILE "minishell: no such file or directory\n"
# define NO_CMD "minishell: %s: command not found\n"
# define NO_PATH "Error: no path to the command\n"
# define ERR_PWD "Error: update_pwd failed\n"
# define ERR_OLDPWD "Error: update_oldpwd failed\n"
# define ERR_EXECVE "Error: execve failed\n"
# define TMP ".infile.tmp"
# define IS_BUILTIN 42

/////////////////////////////////////////// enum

typedef enum e_mode
{
	PROMPT_MODE,
	EXEC_MODE,
	HEREDOC_MODE,
}	t_mode;

typedef enum e_parsing_error
{
	ERR_MALLOC = -42,
	ERR_PROMPT = -1,
	ALL_OK,
}	t_parsing_error;

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

typedef struct s_file
{
	struct s_file		*next;
	char				*value;
	t_rafter			redirection;
}	t_file;

typedef struct s_token
{
	struct s_token	*next;
	char			**cmd;
	t_file			*ls_infile;
	t_file			*ls_outfile;
}	t_token;

typedef struct s_data
{
	t_env	*ls_env;
	t_token	*ls_token;
	t_mode	mode;
	int		pipe_nbr;
	int		exit_status;
}	t_data;

typedef struct s_parsing
{
	int				pipe_seg;
	int				p_index;
	int				word_length;
	char			skip;
	char			*prompt;
	char			*old_prompt;
	char			**prompt_tab;
	bool			dollar;
	bool			simple_quote;
	bool			double_quote;
	bool			outfile_issue;
	t_parsing_error	errcode;
	t_data			*data;
}	t_parsing;

//////////////////////////////////////// functions
void test_signal(void);
/*EXEC*/
/*execution.c*/
int		execution(t_data *data);
/*command.c*/
char	*find_cmd(char **env, char *cmd);
/*itils_cmd.c*/
size_t	find_path_in_env(char **env);
void	fill_tab_null(char **table, size_t len);
/*utils_exec.c*/
char	*ft_strtrim_improved(char *s1, char const *set);
size_t	tablen(char **table);
int		wait_for_pid(t_token *token, pid_t *pid);
char	**get_env_in_tab(t_env *node_env);
int		exec_single_builtin(t_data *data);
size_t	count_cmds(t_token *token);
/*clean.c*/
void	close_free_token_env_pids(t_data *data, int fd0, int fd1, pid_t *pids);
void	free_token_env(t_data *data);
void	close_all(int fd0, int fd1);
void	close_free_token_env(t_data *data, int fd0, int fd1);
void	close_free_array_str(int fd0, int fd1, char **env, char *path);
/*error_exec.c*/
void	msg_exit(char *message, char *arg, int exit_value);
int		msg_return(char *message, char *arg, int return_value);
char	*msg_return_str(char *message, char *arg, char *return_value);
int		perror_return(char *message, int return_value);
int	end_single_cmd(t_data *data, int *io_fd, int *save, int return_val);
/*children.c*/
int		loop_children(t_data *data, pid_t *pids);
/*input_output.c*/
int		redirect_and_exec(t_token *current, int *io_fd, t_data *data, int *save_std_io);
int		get_input(t_file *ls_infile, int previous_pipe);
int		get_output(t_file *ls_outfile, int pipe_output, int count_cmd);
/*manage_heredoc.c*/
int 	here_doc(char *eof);
/*BUILTINS*/
int		cmd_is_builtin(char *path_cmd);
int		exec_homemade_builtin(t_data *data, t_token *current, int *save_std_io);
int		var_cmp(char *s1, char *s2);
void	exec_echo(char **cmd);
int		exec_export(t_env *ls_env, char **cmds);
int		exec_pwd(void);
void	exec_env(t_env *ls_env);
void	exec_env_export(t_env *ls_env);
void	exec_unset(t_env **ls_env, char **cmds);
int		exec_cd(char **cmd, t_env *list_env);
int		exec_exit(t_data *data, t_token *cmds,int *save_std_io);
/*atoull.c*/
unsigned long long	ft_atoull(const char *str, int *minus);

/*PARSING*/
/*cmd_token_utils.c*/
void 	find_all_cmds(char *clean_cmd, char *prompt);
/*cmd_token.c*/
char	*extract_clean_cmd(t_parsing *parsing, char *prompt);
int		skip_io(char *prompt, int i);
char	*extract_current_cmd(char *prompt, int *i, int *j, char *clean_cmd);
/*expand_var.c*/
void	quote_check(char c, t_parsing *parsing);
void	expand_var(t_parsing *parsing);
/*extract_token_without_quotes.c*/
char	*extract_token_without_quotes(char *str, t_parsing *parsing);
/*find_var_name_utils.c*/
int		we_are_in_var_name(t_parsing *parsing, char c);
int 	first_var_name_char_is_valid(char c);
/*ft_coutpipe_utils.c*/
int		prompt_begins_with_a_pipe(const char *s, int *i, t_parsing *parsing);
int		parse_pipe_segments(char const *s, char c, int i);
/*linked_list_token.c*/
t_token	*token_lstnew(void);
t_token	*token_lstlast(t_token *lst);
void	token_lstadd_back(t_token **lst, t_token *new);
/*linked_list_file.c*/
t_file	*file_lstnew(void);
void	file_lstadd_back(t_file **lst, t_file *new);
/*manage_dollar*/
void	manage_dollar_sign(t_parsing *parsing);
char	*prompt_with_content(char *content, int start, t_parsing *parsing);
/*manage_dollar_utils*/
char	*find_var_name(t_parsing *parsing);
int		find_var_end(char *prompt, int p_index);
char	*search_and_fill_content_with_env(t_env *tmp, char *var, int var_len);
int		handle_exit_status_var(t_parsing *parsing);
/*manage_quotes.c*/
int		manage_quotes(char c, t_parsing *parsing);
/*parsing.c*/
void	ft_parsing(t_data *data, t_parsing *parsing);
/*pip_segmentation.c*/
char	**pipe_segmentation(t_parsing *parsing, char c);
/*prompt_check.c*/
int		prompt_check(char *prompt, t_parsing *parsing);
/*rafter_token_utils.c*/
char	*find_redir_file_name(char *prompt, int i, t_parsing *parsing);
/*rafter_token.c*/
int		manage_rafters(t_data *data, int *i, char *prompt, t_parsing *parsing);
/*skip_quote.c*/
int		skip_quote(const char *str, int *i);
/*split_whitespace_quote.c*/
char	**split_whitespace_quotes(char const *s, char c, t_parsing *parsing);
/*tokenisation.c*/
void	tokenisation(t_data *data, t_parsing *parsing);


/*UTILS*/
/*cutstr.c*/
char	*ft_cutstr(char const *s, unsigned int start);
/*debug_print.c*/
void	print_env(t_env *env);
void	print_prompt_tab(char **p_tab);
void	print_tokens(t_data *data);
/*free_minishell.c*/
void	free_parsing(t_parsing *parsing);
void	close_free_maybe_exit(t_parsing *parsing, int exitcode);
/*free_utils.c*/
char	*free_array(char **array);
void	free_env(t_env *env);
void	free_token(t_token *token);
/*ft_isspace.c*/
int		ft_isspace(char c);
/*main_utils.c*/
void	ignore_ac_av(int ac, char **av);
void	parse_and_execute(t_parsing *parsing, t_data *data);
void	process_empty_prompt(t_parsing *parsing);
int		takes_a_value(void);


/*MAIN*/
/*struct_init.c*/
int		struct_init(t_data *data, t_parsing *parsing);
int		env_init(char **env, t_data *data);
/*signals.c*/
void	set_signals_on(t_mode mode);
void	heredoc_handler(int signal);

#endif
