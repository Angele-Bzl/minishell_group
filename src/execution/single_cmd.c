#include "minishell.h"
#include <fcntl.h>

static int	get_input_single_cmd(t_file *ls_infile, int *save_std_io, int *exit_status)
{
	int		input;
	t_file	*current;

	save_std_io[0] = dup(STDIN_FILENO);
	if (save_std_io[0] == ERR)
	{
		*exit_status = EXIT_SYSTEM;
		return (perror_return("dup2", ERR));
	}
	input = STDIN_FILENO;
	if (ls_infile->value)
	{
		current = ls_infile;
		while (current)
		{
			input = open(current->value, O_RDONLY);
			if (input == -1)
			{
				*exit_status = EXIT_PROMPT;
				return (perror_return(current->value, ERR));
			}
			if (current->redirection == DOUBLE_LEFT)
				unlink(current->value);
			if (current->next)
				close(input);
			current = current->next;
		}
	}
	return (input);
}

static int	get_output_single_cmd(t_file *ls_outfile, int *save_std_io, int *exit_status)
{
	int		output;
	t_file	*curr;

	save_std_io[1] = dup(STDOUT_FILENO);
	if (save_std_io[1] == ERR)
	{
		*exit_status = EXIT_SYSTEM;
		return (perror_return("dup2", ERR));
	}
	output = STDOUT_FILENO;
	if (ls_outfile->value)
	{
		curr = ls_outfile;
		while (curr)
		{
			if (curr->redirection == SIMPLE_RIGHT)
				output = open(curr->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (curr->redirection == DOUBLE_RIGHT)
				output = open(curr->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (output == -1)
			{
				*exit_status = EXIT_PROMPT;
				return (perror_return(curr->value, ERR));
			}
			if (curr->next)
				close(output);
			curr = curr->next;
		}
	}
	return (output);
}

static int	reset_dup2(int *save_std_io)
{
	if (dup2(save_std_io[0], STDIN_FILENO) == -1)
		return (perror_return("dup2", ERR));
	if (dup2(save_std_io[1], STDOUT_FILENO) == -1)
		return (perror_return("dup2", ERR));
	close_all(save_std_io[0], save_std_io[1]);
	return (OK);
}

void	exec_single_builtin(t_data *data)
{
	int		io_fd[2];
	int		save_std_io[2];

	io_fd[0] = get_input_single_cmd(data->ls_token->ls_infile, save_std_io, &data->exit_status);
	if (io_fd[0] == ERR)
		return (end_single_cmd(data, io_fd, save_std_io, data->exit_status));
	io_fd[1] = get_output_single_cmd(data->ls_token->ls_outfile, save_std_io, &data->exit_status);
	if (io_fd[1] == ERR)
		return (end_single_cmd(data, io_fd, save_std_io, data->exit_status));
	// data->exit_status = EXIT_OK; //reset here ?
	redirect_and_exec(data->ls_token, io_fd, data, save_std_io);
	if (data->exit_status != EXIT_OK)
		return (end_single_cmd(data, io_fd, save_std_io, data->exit_status));
	if (reset_dup2(save_std_io) == ERR)
		return (end_single_cmd(data, io_fd, save_std_io, ERROR_SYSTEM));
	close_all(io_fd[0], io_fd[1]);
	// data->exit_status = EXIT_OK;
	return ;
}
