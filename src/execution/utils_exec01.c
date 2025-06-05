# include "minishell.h"

int	check_input_output(char *io[2], t_rafter redirection[2], int *io_fd)
{
	io_fd[0] = STDIN_FILENO;
	io_fd[1] = STDOUT_FILENO;
	if (io[0])
	{
		if (redirection[0] == SIMPLE_RIGHT)
			io_fd[0] = open(io[0], O_RDONLY);
		else if (redirection[1] == DOUBLE_RIGHT)
			/*heredoc*/
		if (io_fd[0] == -1)
		{
			perror(io[0]);
			return(0);
		}
	}
	if (io[1])
	{
		if (redirection[1] == SIMPLE_RIGHT)
			io_fd[1] = open(io[1], O_WRONLY | O_TRUNC, 0644);
		else if (redirection[1] == DOUBLE_RIGHT)
			io_fd[1] = open(io[1], O_WRONLY | O_APPEND, 0644);
		if (io_fd[1] == -1)
		{
			close(io_fd[0]);
			perror(io[1]);
			return(0);
		}
	}
	return (1);
}

static int	reset_dup2(t_data *data)
{
	(void)data;
	if (dup2(STDIN_FILENO, STDIN_FILENO))
	{
		// free_all(data);
		perror("dup2");
		return (0);
	}
	if (dup2(STDOUT_FILENO, STDOUT_FILENO))
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
	// char	*path_cmd;
	char	**env;

	if (!check_input_output(data->ls_token->io_value, *data->ls_token->io_redir, io_fd)) //open io_fd[0] et io_fd[1]
		return (0);
	env = get_env_in_tab(&data->ls_env);
	if (!env)
	{
		ft_putendl_fd("Error: malloc", STDERR_FILENO);
		return (0);
	}
	// printf("ls env exec single cmd = %s\n", data->ls_env->line);
	redirect_and_exec(data, io_fd, NULL, env);
	if (!reset_dup2(data))
		return (0);
	return (1);
}
