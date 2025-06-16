#include "minishell.h"

int	count_cmds(t_token *token)
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

int	redirect_and_exec(t_data *data, int *io_fd, char *path_cmd, char **env)
{
	if (dup2(io_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (0);
	}
	if (dup2(io_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (0);
	}
	if (io_fd[0] != STDIN_FILENO)
	{
		close(io_fd[0]);
	}
	if (io_fd[1] != STDOUT_FILENO)
	{
		close(io_fd[1]);
	}
	if (cmd_is_builtin(data->ls_token->cmd[0]))
	{
		exec_homemade_builtin(data);
		return (1);
	}
	else if (execve(path_cmd, data->ls_token->cmd, env) == -1)
	{
		ft_putendl_fd("Error: execve failed", STDERR_FILENO);
		return (0);
	}
	return (1);
}

static int	get_input(char *io_value[2], t_rafter redirection[2], int previous_pipe)
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

static int	get_output(char *io_value[2], t_rafter redirection[2], int pipe_output, int count_cmd)
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

static int	manage_child(t_data *data, int previous_pipe, int pipe_fd[2], pid_t pid)
{
	char	**env;
	char	*path_cmd;
	int		io_fd[2];

	io_fd[0] = get_input(data->ls_token->io_value, data->ls_token->io_redir, previous_pipe);
	io_fd[1] = get_output(data->ls_token->io_value, data->ls_token->io_redir, pipe_fd[1], count_cmds(data->ls_token));
	if (io_fd[0] == -1 || io_fd[1] == -1)
	{
		/*free and exit*/
	}
	env = get_env_in_tab(&data->ls_env);
	data->ls_env = data->env_head;
	if (!env)
	{
		ft_putendl_fd("Error: malloc", STDERR_FILENO);
		exit(ERR);
	}
	path_cmd = find_cmd(env, data->ls_token->cmd[0]);
	if (!path_cmd)
	{
		free(env);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(io_fd[0]);
		close(io_fd[1]);
		ft_putendl_fd("Error: No path to the command.", STDERR_FILENO);
		exit(ERR);
	}
	else if (!redirect_and_exec(data, io_fd, path_cmd, env))
	{
		free(env);
		free(path_cmd);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(io_fd[0]);
		close(io_fd[1]);
		exit(ERR);
	}
	if (pid == 0)
		exit(0);
	return (1);
}

static int	create_children(t_data *data, int *pipe_fd, pid_t *pid, int i)
{
	int	previous_pipe;

	previous_pipe = STDIN_FILENO;
	if (i > 0)
		previous_pipe = pipe_fd[0];
	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe");
		return (0);
	}
	pid[i] = fork();
	if (pid[i] == -1)
	{
		perror("fork");
		return (0);
	}
	if (pid[i] == 0)
	{
		close(pipe_fd[0]);
		manage_child(data, previous_pipe, pipe_fd, pid[i]);
	}
	if (previous_pipe != STDIN_FILENO)
		close(previous_pipe);
	close(pipe_fd[1]);
	return (1);
}

int	execution(t_data *data)
{
	pid_t	*pids;
	int		pipe_fd[2];
	int		i;

	if (!data->ls_token->cmd || !data->ls_token->cmd[0])
	{
		/*free*/
		return (1);
	}
	if (!data->ls_token->next && cmd_is_builtin(data->ls_token->cmd[0]))
	{
		if (!exec_single_cmd(data))
		{
			return (0);
		}
		return (1);
	}
	pids = malloc(sizeof(pid_t) * count_cmds(data->ls_token));
	if (!pids)
	{
		ft_putendl_fd("Error: pids malloc", STDERR_FILENO);
		return (0);
	}
	data->ls_token = data->token_head;
	i = 0;
	while (data->ls_token)
	{
		if (!create_children(data, pipe_fd, pids, i))
		{
			return (0);
		}
		data->ls_token = data->ls_token->next;
		i++;
	}
	close(pipe_fd[0]);
	data->ls_token = data->token_head;
	wait_for_pid(data->ls_token, pids);
	data->ls_token = data->token_head;
	return (1);
}
/*------------------------------------------------------------------------*/

// /*parsing*/
// if (open(fd) == -1)
// {
// 	free_all_parsing(parsing);
// 	errormsg_close_free_exit(parsing->data, perror(file_name), NULL, ERR);
// }
// fais tes trucs
// free_all_parsing(parsing)
// return (OK);

// HELLO(jhgfds)
// {
// 	if (">    >")
// 	{
// 		free_all_parsing(parsing);
// 		errormsg_close_free_return(parsing->data, RAFTERSPACE, NULL, ERR);
// 	}
// 	fais tes trucs
// 	free_all_parsing(parsing)
// 	return (OK);
// }

// if (HELLO(arguement) != OK)
// {
// 	return (ERR);
// }


// /*exec*/
// if (open(fd) == -1)
// {
// 	errormsg_close_free_exit(data, perror(file_name), fd, ERR);
// }
// fais tes trucs
// errormsg_close_free_exit(data, NULL, NULL, OK)


// free_all_parsing(parsing)
// {
// 	free(parsing->prout);
// 	free(parsing->prout1);
// 	free(parsing->prout2);
// }

// errormsg_close_free_exit(t_data *data, char *errormsg, void *argument, int exitcode)
// {
// 	if (errormsg)
// 		ft_printf_err(errormsg, argument);
// 	close_all(data->fd);
// 	free_all(data->trucafree);
// 	exit(exitcode);
// }
// errormsg_close_free_return(t_data *data, char *errormsg, void *argument, int exitcode)
// {
// 	if (errormsg)
// 		ft_printf_err(errormsg, argument);
// 	close_all(data->fd);
// 	free_all(data->trucafree);
// 	return(exitcode);
// }