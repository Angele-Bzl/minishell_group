#include "minishell.h"
#include <signal.h>

int	manage_child(t_data *data, int prev_out, int pipe_fd[2], t_token *current)
{
	int		io_fd[2];

	io_fd[0] = get_input(current->ls_infile, prev_out);
	if (io_fd[0] == ERR)
		return (EXIT_FAILURE);
	io_fd[1] = get_output(current->ls_outfile, pipe_fd[1], count_cmds(current));
	if (io_fd[0] == HEREDOC_INTERRUPTED)
	{
		close(io_fd[0]);
		return (EXIT_FAILURE);
	}
	else if (io_fd[1] == ERROR_PROMPT)
		return (EXIT_PROMPT);
	data->exit_status = EXIT_OK;
	if (redir_exec(current, io_fd, data, NULL) != OK)
	{
		close_all(io_fd[0], io_fd[1]);
		return (data->exit_status);
	}
	return (OK);
}

static int	set_up_pipe(int *i, int *pipe_fd, t_token *token, t_token *current)
{
	int	previous_output;

	previous_output = pipe_fd[0];
	if (count_cmds(token) - count_cmds(current) == 0)
	{
		*i = 0;
		previous_output = STDIN_FILENO;
	}
	if (pipe(pipe_fd) == -1)
	{
		*i = *i + 1;
		return (ERR);
	}
	return (previous_output);
}

static int	exec_child(int *pipe_fd, t_data *data, int prev_outp, t_token *curr)
{
	int	return_value;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(pipe_fd[0]);
	return_value = manage_child(data, prev_outp, pipe_fd, curr);
	return (return_value);
}

int	create_children(t_data *data, int *pipe_fd, pid_t *pids, t_token *current)
{
	int			previous_output;
	static int	i = 0;
	int			return_value;

	previous_output = set_up_pipe(&i, pipe_fd, data->ls_token, current);
	if (previous_output == ERR)
		perror_return("Pipe", ERR);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pids[i] = fork();
	if (pids[i] == -1)
	{
		i++;
		return (perror_return("Fork", ERR));
	}
	if (pids[i++] == 0)
	{
		return_value = exec_child(pipe_fd, data, previous_output, current);
		close_free_token_env_pids(data, previous_output, pipe_fd[1], pids);
		exit(return_value);
	}
	if (previous_output != STDIN_FILENO)
		close(previous_output);
	close(pipe_fd[1]);
	return (OK);
}

int	loop_children(t_data *data, pid_t *pids)
{
	int		pipe_fd[2];
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
