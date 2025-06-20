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
	return(return_value);
}
