#include "minishell.h"

static int	manage_child(t_data *data, int previous_pipe, int pipe_fd[2])
{
	char	**env;
	char	*path_cmd;
	int		io_fd[2];

	io_fd[0] = get_input(data->ls_token->io_value, data->ls_token->io_redir, previous_pipe);
	io_fd[1] = get_output(data->ls_token->io_value, data->ls_token->io_redir, pipe_fd[1], count_cmds(data->ls_token));
	if (io_fd[0] == -1 || io_fd[1] == -1)
		return (free_str_close_fds_return(NULL, NULL, io_fd, 0));
	env = get_env_in_tab(&data->ls_env);
	if (!env)
		return (msg_return("Error: malloc", STDERR_FILENO, 0));
	path_cmd = find_cmd(env, data->ls_token->cmd[0]);
	if (!path_cmd)
	{
		free_str_close_fds(env, NULL, io_fd);
		return (msg_return("Error: No path to the command.", STDERR_FILENO, 0));
	}
	if (!redirect_and_exec(data, io_fd, path_cmd, env))
		return (free_str_close_fds_return(env, path_cmd, io_fd, 0));
	return (1);
}

static int	create_children(t_data *data, int *pipe_fd, pid_t *pids, int i)
{
	int	previous_pipe;

	previous_pipe = STDIN_FILENO;
	if (i > 0)
		previous_pipe = pipe_fd[0];
	if (pipe(pipe_fd) == -1)
		return (perror_return("Pipe", 0));
	pids[i] = fork();
	if (pids[i] == -1)
		return (perror_return("Fork", 0));
	if (pids[i] == 0)
	{
		close(pipe_fd[0]);
		if (!manage_child(data, previous_pipe, pipe_fd))
		{
			free(pids);
			close_fds(previous_pipe, pipe_fd[1]);
			free_data_exit(data, ERR);
		}
	}
	if (previous_pipe != STDIN_FILENO)
		close(previous_pipe);
	close(pipe_fd[1]);
	return (1);
}

int	loop_children(t_token *current, t_data *data, pid_t *pids)
{
	int	i;
	int	pipe_fd[2];

	i = 0;
	while (current)
	{
		data->ls_token = current;
		if (!create_children(data, pipe_fd, pids, i))
			return (0);
		current = current->next;
		i++;
	}
	close(pipe_fd[0]);
	return (1);
}
