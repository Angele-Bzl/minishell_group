#include "minishell.h"

int	manage_child(t_data *data, int previous_pipe, int pipe_fd[2], pid_t pid)
{
	char	**env;
	char	*path_cmd;
	int		io_fd[2];

	io_fd[0] = get_input(data->ls_token->io_value, data->ls_token->io_redir, previous_pipe);
	io_fd[1] = get_output(data->ls_token->io_value, data->ls_token->io_redir, pipe_fd[1], count_cmds(data->ls_token));
	if (io_fd[0] == -1 || io_fd[1] == -1)
	{
		/*free and exit*/
	}
	env = get_env_in_tab(data->ls_env);
	//data->ls_env = data->env_head;
	if (!env)
	{
		ft_putendl_fd("Error: malloc", STDERR_FILENO);
		exit(ERR);
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
		exit(ERR);
	}
	else if (!redirect_and_exec(data, io_fd, path_cmd, env))
	{
		free(env);
		free(path_cmd);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(io_fd[0]);
		close(io_fd[1]);
		exit(ERR);
	}
	if (pid == 0)
		exit(0);
	return (1);
}

int	create_children(t_data *data, int *pipe_fd, pid_t *pid, int i)
{
	int	previous_pipe;

	previous_pipe = STDIN_FILENO;
	if (i > 0)
		previous_pipe = pipe_fd[0];
	if (pipe(pipe_fd) == -1)
		return (perror_return("Pipe", ERR));
	pid[i] = fork();
	if (pid[i] == -1)
		return (perror_return("Fork", ERR));
	if (pid[i] == 0)
	{
		close(pipe_fd[0]);
		manage_child(data, previous_pipe, pipe_fd, pid[i]);
	}
	if (previous_pipe != STDIN_FILENO)
		close(previous_pipe);
	close(pipe_fd[1]);
	return (OK);
}

int	loop_children(t_data *data, t_token *current, pid_t *pids)
{
	int	i;
	int	pipe_fd[2];

	i = 0;
	while (current)
	{
		data->ls_token = current;
		if (create_children(data, pipe_fd, pids, i) != OK)
			return (ERR);
		current = current->next;
		i++;
	}
	close(pipe_fd[0]);
	return (OK);
}
