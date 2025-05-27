# include "minishell.h"

/*
Check the input access
Check the output access
Check the cmd
*/

int	redirect_and_exec(t_data *data, int *io_fd, char *path_cmd, int previous_output, char **env)
{
	if (dup2(previous_output, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (0);
	}
	if (dup2(io_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (0);
	}
	if (cmd_is_builtin(data->ls_token->cmd[0]))
			exec_homemade_builtin(data, env);
	if (execve(path_cmd, data->ls_token->cmd, env) == -1)
	{
		ft_putendl_fd("Error: execve failed", STDERR_FILENO);
		return (0);
	}
	return (1);
}

static int	create_children(t_data *data, int *pipe_fd, pid_t pid, int i)
{
	int		previous_output;
	int		io_fd[2];
	char	*path_cmd;
	char	**env;


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
	{
		if (!check_input_output(data->ls_token->io_value, *data->ls_token->io_redir, io_fd)) //open io_fd[0] et io_fd[1]
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			return (0);
		}
		env = get_env_in_tab(data->ls_env);
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
		else if (!redirect_and_exec(data, io_fd, path_cmd, previous_output, env))
		{
			free(env);
			free(path_cmd);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			close(io_fd[0]);
			close(io_fd[1]);
			return (0);
		}
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (1);
}

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

int	execution(t_data *data)
{
	pid_t	*pids;
	int		pipe_fd[2];
	int		i;

	if (!data->ls_token->next)
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
