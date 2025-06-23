#include "minishell.h"

int	redirect_and_exec(t_data *data, int *io_fd, char *path_cmd, char **env)
{
	if (dup2(io_fd[0], STDIN_FILENO) == -1)
		return (perror_return("dup2", ERR));
	if (dup2(io_fd[1], STDOUT_FILENO) == -1)
		return (perror_return("dup2", ERR));
	close_all(io_fd[0], io_fd[1]);
	if (cmd_is_builtin(data->ls_token->cmd[0]))
		return (exec_homemade_builtin(data));
	if (execve(path_cmd, data->ls_token->cmd, env) == -1)
		return (msg_return("Error: execve failed", STDERR_FILENO, ERR));
	return (OK);
}

int	get_input(t_infile *ls_infile, int previous_pipe)
{
	int	input;
	t_infile	*current;

	input = previous_pipe;
	if (ls_infile->value)
	{
		current = ls_infile;
		while (current)
		{
			if (current->redirection == SIMPLE_LEFT)
				input = open(current->value, O_RDONLY);
			if (current->redirection == DOUBLE_LEFT)
				input = here_doc(current->value);
			if (input == -1)
				perror_return(ls_infile->value, ERROR_SYSTEM);
			if (ls_infile->redirection == DOUBLE_LEFT)
				unlink(ls_infile->value);
			if (current->next)
				close(input);
			current = current->next;
		}
		close(previous_pipe);
	}
	return (input);
}

int	get_output(t_outfile *ls_outfile, int pipe_output, int count_cmd)
{
	int	output;
	t_outfile	*current;

	if (count_cmd == 1)
	{
		close(pipe_output);
		output = STDOUT_FILENO;
	}
	if (ls_outfile->value)
	{
		if (count_cmd != 1)
			close(pipe_output);
		current = ls_outfile;
		while (current)
		{
			if (current->redirection == SIMPLE_RIGHT)
				output = open(current->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (current->redirection == DOUBLE_RIGHT)
				output = open(current->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (output == -1)
				perror_return(ls_outfile->value, ERROR_SYSTEM);
			if (current->next)
				close(output);
			current = current->next;
		}
	}
	return (output);
}
