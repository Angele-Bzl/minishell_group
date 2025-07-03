#include "minishell.h"

void	msg_exit(char *message, char *arg, int exit_value)
{
	if (message)
		ft_printf_err(message, arg);
	exit(exit_value);
}

int	msg_return(char *message, char *arg, int return_value)
{
	if (message)
		ft_printf_err(message, arg);
	return (return_value);
}

char	*msg_return_str(char *message, char *arg, char *return_value)
{
	if (message)
		ft_printf_err(message, arg);
	return (return_value);
}

int	perror_return(char *message, int return_value)
{
	if (message)
		perror(message);
	return (return_value);
}

int	end_single_cmd(t_data *data, int *io_fd, int *save, int return_val)
{
	free_env(data->ls_env);
	close_all(io_fd[0], io_fd[1]);
	close_all(save[0], save[1]);
	if (return_val == ERROR_PROMPT)
		return (ERR);
	else if (return_val == ERROR_SYSTEM)
		exit(STDERR_FILENO);
	return (OK);
}
