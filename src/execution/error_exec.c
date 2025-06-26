#include "minishell.h"

void	msg_exit(char *message, int fd, int exit_value)
{
	if (message)
		ft_putendl_fd(message, fd);
	exit(exit_value);
}

int	msg_return(char *message, int fd, int return_value)
{
	if (message)
		ft_putendl_fd(message, fd);
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

int	msg_return_close_all(int *fds, char *message, int fd, int return_value)
{
	close_all(fds[0], fds[1]);
	return (msg_return(message, fd, return_value));
}
