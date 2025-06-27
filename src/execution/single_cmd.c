#include "minishell.h"

static int	get_input_single_cmd(t_file *ls_infile, int *save_std_io)
{
	int		input;
	t_file	*current;

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
				return (perror_return(ls_infile->value, ERR));
			if (current->next)
				close(input);
			current = current->next;
		}
	}
	return (input);
}

static int	get_output_single_cmd(t_file *ls_outfile, int *save_std_io)
{
	int		output;
	t_file	*curr;

	save_std_io[1] = dup(STDOUT_FILENO);
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
				return (perror_return(ls_outfile->value, ERR));
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

int	exec_single_cmd(t_data *data)
{
	int		io_fd[2];
	int		save_std_io[2];
	int		return_value;

	io_fd[0] = get_input_single_cmd(data->ls_token->ls_infile, save_std_io);
	io_fd[1] = get_output_single_cmd(data->ls_token->ls_outfile, save_std_io);
	if (io_fd[0] == ERR || io_fd[1] == ERR)
		return (end_single_cmd(data, io_fd, save_std_io, ERROR_SYSTEM));
	if (!ft_strncmp(data->ls_token->cmd[0], "exit\0", 5))
		close_all(save_std_io[0], save_std_io[1]);
	return_value = redirect_and_exec(data->ls_token, io_fd, data);
	if (return_value != OK)
		return (end_single_cmd(data, io_fd, save_std_io, return_value));
	if (reset_dup2(save_std_io) == ERR)
		return (end_single_cmd(data, io_fd, save_std_io, ERROR_SYSTEM));
	close_all(io_fd[0], io_fd[1]);
	return (OK);
}
