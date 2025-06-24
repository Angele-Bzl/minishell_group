#include "minishell.h"

int	manage_child(t_data *data, int previous_pipe, int pipe_fd[2], t_token *current)
{
	char	**env;
	char	*path_cmd;
	int		io_fd[2];

	io_fd[0] = get_input(current->ls_infile, previous_pipe);
	io_fd[1] = get_output(current->ls_outfile, pipe_fd[1], count_cmds(current));
	if (io_fd[0] == ERR || io_fd[1] == ERR)
	{
		close_all(io_fd[0], io_fd[1]);
		return (EXIT_FAILURE);
	}
	env = get_env_in_tab(data->ls_env);
	if (!env)
	{
		close_all(io_fd[0], io_fd[1]);
		return (msg_return(MALLOC, STDERR_FILENO, EXIT_FAILURE));
	}
	path_cmd = find_cmd(env, current->cmd[0]);
	if (!path_cmd)
	{
		free_array(env);
		close_all(io_fd[0], io_fd[1]);
		return (EXIT_FAILURE);
	}
	if (redirect_and_exec(current, io_fd, path_cmd, env) != OK)
	{
		free_array(env);
		free(path_cmd);
		close_all(io_fd[0], io_fd[1]);
		return (EXIT_FAILURE);
	}
	free_array(env);
	// free(path_cmd);
	return (IS_BUILTIN); //si on arrive ici ça veut dire qu'on est passé par un builtin donc OK, mais on exit quand meme apres
}

int	create_children(t_data *data, int *pipe_fd, pid_t *pids, t_token *current)
{
	int	previous_pipe;
	int	return_value;
	static int	i = 0;

	previous_pipe = pipe_fd[0];
	printf("cmd = %d\n", count_cmds(data->ls_token) - count_cmds(current));
	if (count_cmds(data->ls_token) - count_cmds(current) == 0)
	{
		i = 0;
		previous_pipe = STDIN_FILENO;
	}
	if (pipe(pipe_fd) == -1)
	{
		i++;
		return (perror_return("Pipe", ERR));
	}
	printf("i = %d\n", i);
	pids[i] = fork();
	if (pids[i] == -1)
	{
		i++;
		return (perror_return("Fork", ERR));
	}
	if (pids[i] == 0)
	{
		close(pipe_fd[0]);
		return_value = manage_child(data, previous_pipe, pipe_fd, current);
		close_free_token_env_pids(data, previous_pipe, pipe_fd[1], pids);
		exit(return_value);
	}
	if (previous_pipe != STDIN_FILENO)
		close(previous_pipe);
	close(pipe_fd[1]);
	i++;
	return (OK);
}

int	loop_children(t_data *data, pid_t *pids)
{
	int	pipe_fd[2];
	t_token	*current;

	current = data->ls_token;
	while (current)
	{
		if (create_children(data, pipe_fd, pids, current) != OK)
			return (ERR);
		current = current->next;
	}
	close(pipe_fd[0]);
	return (OK);
}
