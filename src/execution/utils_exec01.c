#include "minishell.h"

static int	input_output_single_cmd(char *io_value[2], t_rafter redirection[2], int *io_fd, int *save_std_io)
{
	if (save_std_io)
	{
		save_std_io[0] = dup(STDIN_FILENO);
		save_std_io[1] = dup(STDOUT_FILENO);
	}
	io_fd[0] = STDIN_FILENO;
	io_fd[1] = STDOUT_FILENO;
	if (io_value[0])
	{
		io_fd[0] = open(io_value[0], O_RDONLY);
		if (redirection[1] == DOUBLE_LEFT)
			unlink(io_value[0]);
		if (io_fd[0] == -1)
		{
			perror(io_value[0]);
			return (0);
		}
	}
	if (io_value[1])
	{
		if (redirection[1] == SIMPLE_RIGHT)
			io_fd[1] = open(io_value[1], O_WRONLY | O_TRUNC, 0644);
		else if (redirection[1] == DOUBLE_RIGHT)
			io_fd[1] = open(io_value[1], O_WRONLY | O_APPEND, 0644);
		if (io_fd[1] == -1)
		{
			close(io_fd[0]);
			perror(io_value[1]);
			return (0);
		}
	}
	return (1);
}

static int	reset_dup2(t_data *data, int *save_std_io)
{
	(void)data;
	if (dup2(save_std_io[0], STDIN_FILENO) == -1)
	{
		// free_all(data);
		perror("dup2");
		return (0);
	}
	if (dup2(save_std_io[1], STDOUT_FILENO) == -1)
	{
		// free_all(data);
		perror("dup2");
		return (0);
	}
	return (1);
}

int	exec_single_cmd(t_data *data)
{
	int		io_fd[2];
	int		save_std_io[2];

	if (!input_output_single_cmd(data->ls_token->io_value, data->ls_token->io_redir, io_fd, save_std_io)) //open io_fd[0] et io_fd[1]
		return (0);
	redirect_and_exec(data, io_fd, NULL, NULL);
	if (!reset_dup2(data, save_std_io))
		return (0);
	return (1);
}
