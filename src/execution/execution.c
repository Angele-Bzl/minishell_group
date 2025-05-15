/*
Check the input access
Check the output access
Check the cmd
*/

static int	check_input_output(char *io, int *io_fd)
{
	io_fd[0] = 0;
	io_fd[1] = 1;
	if (io[0])
	{
		io_fd[0] = open(io[0]);
		if (io_fd[0] == -1)
		{
			perror(io[0]);
			return(0);
		}
	}
	if (io[1])
	{
		io_fd[1] = open(io[1]);
		if (io_fd[1] == -1)
		{
			close(io_fd[0]);
			perror(io[1]);
			return(0);
		}
	}
	return (1);
}

static int	redirect_and_exec(t_data *data, int *io_fd, char *path_cmd, int previous_output)
{
	/*comment differencier < de <<, et > de >> ???*/
	if (dup2(previous_output, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (0);
	}
	if (dup2(io_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (0);
	}
	if (execve(path_cmd, data->_token->cmds, data->t_env) == -1)
	{
		ft_putendl("Error: execve failed", STDERR_FILENO);
		return (0);
	}
}

static int	create_children(t_data *data, int *pipe_fd, pid_t pid, int i)
{
	int		previous_output;
	int		io_fd[2];
	char	*path_cmd;

	if (i > 0)
		previous_output = pipe_fd[0];
	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe");
		return (0);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (0);
	}
	if (pid == 0)
	{
		if (!check_input_output(data->token->io, io_fd)) //open io_fd[0] et io_fd[1]
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			return (0);
		}
		path_cmd = find_cmd(data->t_env, data->t_token->cmds[0]);
		if (!path_cmd)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			close(io_fd[0]);
			close(io_fd[1]);
			ft_putendl("Error: No path to the command.");
			return (0);
		}
		if (!redirect_and_exec(data, io_fd, path_cmd, previous_output))//
		{
			free(path_cmd);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			close(io_fd[0]);
			close(io_fd[1]);
			return (0);
		}
	}
	return (1);
}

static int	count_cmds(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		token = token->next;
		i++;
	}
	return (i);
}

int	execution(t_data *data)
{
	pid_t	*pids;
	int		pipe_fd[2];
	int		i;

	pids = malloc(sizeof(pid_t) * count_cmds(data->token));
	if (!pids)
	{
		putendl("Error: pids malloc");
		return (0);
	}
	if (!data->token->next)
	{
		exec_single_cmd();//
		return (1);
	}
	i = 0;
	while (data->token)
	{
		if (!create_children(data, pipe_fd, pids[i], i))
		{
			return (0);
		}
		data->token = data->token->next;
		i++;
	}
	wait_for_pid(data, pids);//
	return (1);
}
