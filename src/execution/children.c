#include "minishell.h"
#include <sys/wait.h>
#include <signal.h>

int	manage_child(t_data *data, int prev_out, int pipe_fd[2], t_token *current)
{
	int		io_fd[2];

	io_fd[0] = get_input(current->ls_infile, prev_out);
	if (io_fd[0] == ERR)
		return (EXIT_FAILURE);
	io_fd[1] = get_output(current->ls_outfile, pipe_fd[1], count_cmds(current));
	if (io_fd[1] == ERR || io_fd[0] == HEREDOC_INTERRUPTED)
	{
		close(io_fd[0]);
		return (EXIT_FAILURE);
	}
	if (redirect_and_exec(current, io_fd, data, NULL) != OK)
	{
		close_all(io_fd[0], io_fd[1]);
		return (EXIT_FAILURE);
	}
	return (IS_BUILTIN);
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

int	create_children(t_data *data, int *pipe_fd, pid_t *pids, t_token *current)
{
	int			previous_output;
	int			return_value;
	static int	i = 0;

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
	if (pids[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(pipe_fd[0]);
		return_value = manage_child(data, previous_output, pipe_fd, current);
		close_free_token_env_pids(data, previous_output, pipe_fd[1], pids);
		exit(return_value);
	}
	if (previous_output != STDIN_FILENO)
		close(previous_output);
	close(pipe_fd[1]);
	i++;
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
