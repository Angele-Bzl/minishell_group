# include "minishell.h"

int	count_cmds(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		token = token->next;
		i++;
	}
	return (i);
}

int	redirect_and_exec(t_data *data, int *io_fd, char *path_cmd, char **env)
{
	if (dup2(io_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (0);
	}
	if (dup2(io_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (0);
	}
	// close(io_fd[0]);
	// close(io_fd[1]);
	if (cmd_is_builtin(data->ls_token->cmd[0]))
	{
		exec_homemade_builtin(data, env);
		return (0); //exit ?
	}
	else if (execve(path_cmd, data->ls_token->cmd, env) == -1)
	{
		ft_putendl_fd("Error: execve failed", STDERR_FILENO);
		return (0);
	}
	return (1);
}

static int	get_input(char *io[2], t_rafter redirection[2], int previous_output)
{
	int	input;

	input = previous_output;
	if (io[0])
	{
		// close(previous_output);
		if (redirection[0] == SIMPLE_LEFT)
			input = open(io[0], O_RDONLY);
		else if (redirection[0] == DOUBLE_LEFT)
			/*heredoc*/
		if (input == -1)
		{
			perror(io[0]);
			return(-1);
		}
	}
	return (input);
}

static int	get_output(char *io[2], t_rafter redirection[2], int pipe_output, int count_cmd)
{
	int	output;

	if (count_cmd == 1)
		output = STDOUT_FILENO;
	else
		output = pipe_output;
	if (io[1])
	{
		// close(pipe_output);
		if (redirection[1] == SIMPLE_RIGHT)
			output = open(io[1], O_WRONLY | O_TRUNC, 0644);
		else if (redirection[1] == DOUBLE_RIGHT)
			output = open(io[1], O_WRONLY | O_APPEND, 0644);
		if (output == -1)
		{
			perror(io[1]);
			return(-1);
		}
	}
	return (output);
}

static int	manage_child(t_data *data, int previous_output, int pipe_fd[2])
{
	char	**env;
	char	*path_cmd;
	int		io_fd[2];

	io_fd[0] = get_input(data->ls_token->io_value, *data->ls_token->io_redir, previous_output);
	io_fd[1] = get_output(data->ls_token->io_value, *data->ls_token->io_redir, pipe_fd[1], count_cmds(data->ls_token));
	env = get_env_in_tab(&data->ls_env);
	data->ls_env = data->env_head;
	if (!env)
	{
		ft_putendl_fd("Error: malloc", STDERR_FILENO);
		return (0);
	}
	path_cmd = find_cmd(env, data->ls_token->cmd[0]);
	if (!path_cmd)
	{
		free(env);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(io_fd[0]);
		close(io_fd[1]);
		ft_putendl_fd("Error: No path to the command.", STDERR_FILENO);
		return (0);
	}
	else if (!redirect_and_exec(data, io_fd, path_cmd, env))
	{
		free(env);
		free(path_cmd);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(io_fd[0]);
		close(io_fd[1]);
		return (0);
	}
	return (1);
}

static int	create_children(t_data *data, int *pipe_fd, pid_t pid, int i)
{
	int		previous_output;

	previous_output = 0;
	if (i > 0)
		previous_output = pipe_fd[0];
	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe");
		return (0);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (0);
	}
	if (pid == 0)
		manage_child(data, previous_output, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (1);
}

int	execution(t_data *data)
{
	pid_t	*pids;
	int		pipe_fd[2];
	int		i;

	if (!data->ls_token->cmd[0])
		return (1);
	if (!data->ls_token->next && cmd_is_builtin(data->ls_token->cmd[0]))
	{
		exec_single_cmd(data);
		return (1);
	}
	pids = malloc(sizeof(pid_t) * count_cmds(data->ls_token));
	if (!pids)
	{
		ft_putendl_fd("Error: pids malloc", STDERR_FILENO);
		return (0);
	}
	data->ls_token = data->token_head;
	i = 0;
	while (data->ls_token)
	{
		if (!create_children(data, pipe_fd, pids[i], i))
		{
			return (0);
		}
		data->ls_token = data->ls_token->next;
		i++;
	}
	data->ls_token = data->token_head;
	wait_for_pid(data->ls_token, pids);
	data->ls_token = data->token_head;
	return (1);
}
