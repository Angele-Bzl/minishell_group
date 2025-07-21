#include "minishell.h"

int	parsing_error_int(t_parsing *parsing, int errcode, int ex_stat, int ret_val)
{
	if (ex_stat)
		parsing->data->exit_status = ex_stat;
	if (errcode)
	{
		if (errcode == ERR_MALLOC)
			printf(MALLOC);
		parsing->errcode = errcode;
	}
	return (ret_val);
}

char	*parsg_err_str(t_parsing *pars, int errcode, int ex_stat, char *ret_val)
{
	if (ex_stat)
		pars->data->exit_status = ex_stat;
	if (errcode)
	{
		if (errcode == ERR_MALLOC)
			printf(MALLOC);
		pars->errcode = errcode;
	}
	return (ret_val);
}

void	parsing_error_void(t_parsing *parsing, int errcode, int exit_status)
{
	if (exit_status)
		parsing->data->exit_status = exit_status;
	if (errcode)
	{
		if (errcode == ERR_MALLOC)
			printf(MALLOC);
		parsing->errcode = errcode;
	}
	return ;
}
