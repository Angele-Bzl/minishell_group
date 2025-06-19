#include "minishell.h"

static int	ioput_single_cmd(char *io_value[2], t_rafter redirection[2], int *io_fd, int *save_std_io)
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
			return (perror_return(io_value[0], 0));
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
			return (perror_return(io_value[1], 0));
		}
	}
	return (1);
}

static int	reset_dup2(int *save_std_io)
{
	if (dup2(save_std_io[0], STDIN_FILENO) == -1)
		return (perror_return("dup2", 0));
	if (dup2(save_std_io[1], STDOUT_FILENO) == -1)
		return (perror_return("dup2", 0));
	return (1);
}

int	exec_single_cmd(t_data *data)
{
	int		io_fd[2];
	int		save_std[2];

	if (!ioput_single_cmd(data->ls_token->io_value, data->ls_token->io_redir, io_fd, save_std))
	{
		free_token_and_env(data);
		exit(STDERR_FILENO);
	}
	if (!redirect_and_exec(data, io_fd, NULL, NULL))
		return (ERR);
	if (!reset_dup2(save_std))
	{
		free_token_and_env(data);
		exit(STDERR_FILENO);
	}
	return (OK);
}
