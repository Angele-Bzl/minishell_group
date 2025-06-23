#include "minishell.h"

int	manage_child(t_data *data, int previous_pipe, int pipe_fd[2], pid_t pid)
{
	char	**env;
	char	*path_cmd;
	int		io_fd[2];

	io_fd[0] = get_input(data->ls_token->ls_infile, previous_pipe);
	io_fd[1] = get_output(data->ls_token->ls_outfile, pipe_fd[1], count_cmds(data->ls_token));
	if (io_fd[0] == ERR || io_fd[1] == ERR)
	{
		close_all(io_fd[0], io_fd[1]);
		return (ERR);
	}
	env = get_env_in_tab(data->ls_env);
	if (!env)
	{
		close_all(io_fd[0], io_fd[1]);
		return (msg_return(MALLOC, STDERR_FILENO, ERR));
	}
	path_cmd = find_cmd(env, data->ls_token->cmd[0]);
	if (!path_cmd)
	{
		free_array(env);
		close_all(io_fd[0], io_fd[1]);
		return (ERR);
	}
	else if (redirect_and_exec(data, io_fd, path_cmd, env) != OK)
	{
		free_array(env);
		free(path_cmd);
		close_all(io_fd[0], io_fd[1]);
		return (ERR);
	}
	if (pid == 0)
		return (42); //si on arrive ici ça veut dire qu'on est passé par un builtin donc OK, mais on exit quand meme apres
	return (OK);
}

int	create_children(t_data *data, int *pipe_fd, pid_t *pids, int i)
{
	int	previous_pipe;

	previous_pipe = STDIN_FILENO;
	if (i > 0)
		previous_pipe = pipe_fd[0];
	if (pipe(pipe_fd) == -1)
		return (perror_return("Pipe", ERR));
	pids[i] = fork();
	if (pids[i] == -1)
		return (perror_return("Fork", ERR));
	if (pids[i] == 0)
	{
		close(pipe_fd[0]);
		if (manage_child(data, previous_pipe, pipe_fd, pids[i]) != OK)
		{
			close_free_data_env_pids(data, previous_pipe, pipe_fd[1], pids);
			exit(EXIT_FAILURE);
		}
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
