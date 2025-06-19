#include "minishell.h"

int	redirect_and_exec(t_data *data, int *io_fd, char *path_cmd, char **env)
{
	if (dup2(io_fd[0], STDIN_FILENO) == -1)
	{
		ft_printf_err("io_fd[0] = %d\n", io_fd[0]);
		ft_printf_err("cmd = %s\n", path_cmd);
		return (perror_return("dup2", 0));
	}
	if (dup2(io_fd[1], STDOUT_FILENO) == -1)
	{
		ft_printf_err("io_fd[1] = %d\n", io_fd[1]);
		ft_printf_err("cmd = %s\n", path_cmd);
		return (perror_return("dup2", 0));
	}
	if (io_fd[0] != STDIN_FILENO)
		close(io_fd[0]);
	if (io_fd[1] != STDOUT_FILENO)
		close(io_fd[1]);
	if (cmd_is_builtin(data->ls_token->cmd[0]))
	{
		exec_homemade_builtin(data);
		return (1);
	}
	else if (execve(path_cmd, data->ls_token->cmd, env) == -1)
		return (msg_return("Error: execve failed", STDERR_FILENO, 0));
	return (1);
}

int	get_input(char *io_value[2], t_rafter redirection[2], int previous_pipe)
{
	int	input;

	input = previous_pipe;
	if (io_value[0])
	{
		close(previous_pipe);
		input = open(io_value[0], O_RDONLY);
		if (redirection[0] == DOUBLE_LEFT)
			unlink(io_value[0]);
		if (input == -1)
		{
			perror(io_value[0]);
			return (-1);
		}
	}
	return (input);
}

int	get_output(char *io_value[2], t_rafter redirection[2], int pipe_output, int count_cmd)
{
	int	output;

	if (count_cmd == 1)
	{
		close(pipe_output);
		output = STDOUT_FILENO;
	}
	else
		output = pipe_output;
	if (io_value[1])
	{
		close(pipe_output);
		if (redirection[1] == SIMPLE_RIGHT)
			output = open(io_value[1], O_WRONLY | O_TRUNC, 0644);
		else if (redirection[1] == DOUBLE_RIGHT)
			output = open(io_value[1], O_WRONLY | O_APPEND, 0644);
		if (output == -1)
		{
			perror(io_value[1]);
			return (-1);
		}
	}
	return (output);
}
