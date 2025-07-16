#include "minishell.h"

int	parsing_error_int(t_parsing *parsing, int errcode ,int	exit_status, int return_value)
{
	if (exit_status)
		parsing->data->exit_status = exit_status;
	if (errcode)
		parsing->errcode = errcode;
	return (return_value);
}

char	*parsing_error_char(t_parsing *parsing, int errcode ,int	exit_status, char *return_value)
{
	if (exit_status)
		parsing->data->exit_status = exit_status;
	if (errcode)
		parsing->errcode = errcode;
	return (return_value);
}

void	parsing_error_void(t_parsing *parsing, int errcode ,int	exit_status)
{
	if (exit_status)
		parsing->data->exit_status = exit_status;
	if (errcode)
		parsing->errcode = errcode;
	return ;
}
