/*
Check the input access
Check the output access
Check the cmd
*/

static int	check_input_output(char *io, int *io_fd)
{
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
			perror(io[1]);
			return(0);
		}
	}
	return (1);
}

static int	create_children(t_data *data, pid_t pid)
{
	int		pipe_fd[2];
	int		io_fd[2];

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
		if (!check_input_output(data->token->io, io_fd))
			return (0);
		if (!find_cmd(data))//
			return (0);
		if (!redirect_and_exec(data, io_fd))//
			return (0);
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
	int		i;

	pids = malloc(sizeof(pid_t) * count_cmds(data->token));
	if (!pids)
	{
		putendl("Error: pids malloc");
		retrun (0);
	}
	if (!data->token->next)
	{
		exec_single_cmd();//
		return (1);
	}
	i = 0;
	while (data->token)
	{
		if (!create_children(data, pids[i]))
		{
			return (0);
		}
		data->token = data->token->next;
	}
	wait_for_pid(data, pids);//
	return (1);
}
