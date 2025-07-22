#include "minishell.h"

int	pars_err_int(t_parsing *par, int errcode, int exit_status, int ret_val)
{
	if (exit_status)
		par->data->exit_status = exit_status;
	if (errcode)
	{
		if (errcode == ERR_MALLOC)
			printf(MALLOC);
		par->errcode = errcode;
	}
	return (ret_val);
}

char	*pars_err_char(t_parsing *par, int err, int ex_stat, char *ret_val)
{
	if (ex_stat)
		par->data->exit_status = ex_stat;
	if (err)
	{
		if (err == ERR_MALLOC)
			printf(MALLOC);
		par->errcode = err;
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
