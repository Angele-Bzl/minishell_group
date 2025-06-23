#include "minishell.h"

static int get_input_single_cmd(t_infile *ls_infile, int *save_std_io)
{
	int	input;
	t_infile	*current;

	save_std_io[0] = dup(STDIN_FILENO);
	input = STDIN_FILENO;
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
	}
	return (input);
}

static int	get_output_single_cmd(t_outfile *ls_outfile, int *save_std_io)
{
	int	output;
	t_infile	*current;

	save_std_io[1] = dup(STDOUT_FILENO);
	output = STDOUT_FILENO;
	if (ls_outfile->value)
	{
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

static int	reset_dup2(t_data *data, int *save_std_io)
{
	(void)data;
	if (dup2(save_std_io[0], STDIN_FILENO) == -1)
		return (perror_return("dup2", ERR));
	if (dup2(save_std_io[1], STDOUT_FILENO) == -1)
		return (perror_return("dup2", ERR));
	return (OK);
}

int	exec_single_cmd(t_data *data)
{
	int		io_fd[2];
	int		save_std_io[2];
	int		return_value;

	io_fd[0] = get_input_single_cmd(data->ls_token->ls_infile, save_std_io);
	io_fd[1] = get_output_single_cmd(data->ls_token->ls_infile, save_std_io);
	if (io_fd[0] == ERROR_SYSTEM || io_fd[1] == ERROR_SYSTEM)
	{
		close_free_data_env(data, io_fd[0], io_fd[1]);
		exit(STDERR_FILENO);
	}
	return_value = redirect_and_exec(data, io_fd, NULL, NULL);
	if (return_value != OK)
	{
		close_free_data_env(data, io_fd[0], io_fd[1]);
		if (return_value == ERROR_PROMPT)
			return (ERR);
		else if (return_value == ERROR_SYSTEM)
			exit(STDERR_FILENO);
	}
	if (reset_dup2(data, save_std_io) != OK)
	{
		close_free_data_env(data, io_fd[0], io_fd[1]);
		exit(STDERR_FILENO);
	}
	return (OK);
}
