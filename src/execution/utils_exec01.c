#include "minishell.h"

int	check_input_output(char *io[2], t_rafter redirection[2], int *io_fd)
{
	io_fd[0] = STDIN_FILENO;
	io_fd[1] = STDOUT_FILENO;
	if (io[0])
	{
		if (redirection[0] == SIMPLE_LEFT)
		{
			io_fd[0] = open(io[0], O_RDONLY);
		}
		else if (redirection[1] == DOUBLE_LEFT)
		{
			/*heredoc*/
		}
		if (io_fd[0] == -1)
		{
			perror(io[0]);
			return (0);
		}
	}
	if (io[1])
	{
		// printf("check io : redir[1] = %d\n", redirection[1]);
		if (redirection[1] == SIMPLE_RIGHT)
		{
			// printf("simple right\n");
			io_fd[1] = open(io[1], O_WRONLY | O_TRUNC, 0644);
		}
		else if (redirection[1] == DOUBLE_RIGHT)
			io_fd[1] = open(io[1], O_WRONLY | O_APPEND, 0644);
		if (io_fd[1] == -1)
		{
			close(io_fd[0]);
			perror(io[1]);
			return (0);
		}
	}
	return (1);
}

static int	reset_dup2(t_data *data, int *save_std_io, int *io_fd)
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
	io_fd[0] = -1;
	io_fd[1] = -1;
	return (1);
}

int	exec_single_cmd(t_data *data)
{
	int		io_fd[2];
	char	**env;
	int		save_std_io[2];

	if (!check_input_output(data->ls_token->io_value, data->ls_token->io_redir, io_fd)) //open io_fd[0] et io_fd[1]
		return (0);
	env = get_env_in_tab(&data->ls_env);
	if (!env)
	{
		ft_putendl_fd("Error: malloc", STDERR_FILENO);
		return (0);
	}
	redirect_and_exec(data, io_fd, NULL, env, save_std_io);
	if (!reset_dup2(data, save_std_io, io_fd))
		return (0);
	return (1);
}
