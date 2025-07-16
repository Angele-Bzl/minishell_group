#include "minishell.h"
#include <fcntl.h>

int	redirect_and_exec(t_token *current, int *io_fd, t_data *data, int *save_std)
{
	char	**env;
	char	*path_cmd;

	if (dup2(io_fd[0], 0) == -1 || dup2(io_fd[1], 1) == -1)
		return (perror_return("dup2", ERROR_SYSTEM));
	close_all(io_fd[0], io_fd[1]);
	if (cmd_is_builtin(current->cmd[0]))
		return (exec_homemade_builtin(data, current, save_std));
	env = get_env_in_tab(data->ls_env);
	if (!env)
		return (msg_return(MALLOC, NULL, ERR));
	path_cmd = find_cmd(env, current->cmd[0], &data->exit_status);
	if (!path_cmd)
	{
		free_array(env);
		return (ERR);
		// return (msg_return(NO_FILE, current->cmd[0], ERR));
	}
	else if (access(path_cmd, X_OK) == -1)
	{
		free_array(env);
		data->exit_status = ERROR_PERMISSION;
		return (perror_return(path_cmd, ERR));
	}
	execve(path_cmd, current->cmd, env);
	free_array(env);
	return (msg_return(ERR_EXECVE, NULL, ERR));
}

int	get_input(t_file *ls_infile, int previous_output)
{
	int		input;
	t_file	*current;

	input = previous_output;
	if (ls_infile->value)
	{
		current = ls_infile;
		while (current)
		{
			// if (current->redirection == SIMPLE_LEFT)
			input = open(current->value, O_RDONLY);
			// {
				// 	input = here_doc(current->value);
				// 	if (input == HEREDOC_INTERRUPTED)
				// 		return (HEREDOC_INTERRUPTED);
				// }
			if (input == -1)
				return (perror_return(current->value, ERR));
			if (current->redirection == DOUBLE_LEFT)
				unlink(current->value);
			if (current->next)
				close(input);
			current = current->next;
		}
		if (previous_output != STDIN_FILENO)
			close(previous_output);
	}
	return (input);
}

static int	output_is_std(int pipe_output)
{
	close(pipe_output);
	return (STDOUT_FILENO);
}

int	get_output(t_file *ls_outfile, int pipe_output, int count_cmd)
{
	int		output;
	t_file	*curr;

	output = pipe_output;
	if (count_cmd == 1)
		output = output_is_std(pipe_output);
	if (ls_outfile->value)
	{
		if (count_cmd != 1)
			close(pipe_output);
		curr = ls_outfile;
		while (curr)
		{
			if (curr->redirection == SIMPLE_RIGHT)
				output = open(curr->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (curr->redirection == DOUBLE_RIGHT)
				output = open(curr->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (output == -1)
				return (perror_return(curr->value, ERROR_PROMPT));
			if (curr->next)
				close(output);
			curr = curr->next;
		}
	}
	return (output);
}
