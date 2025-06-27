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
