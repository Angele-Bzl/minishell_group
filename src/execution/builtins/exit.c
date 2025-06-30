#include "minishell.h"
#include <limits.h>

static int	exit_no_arg(t_data *data)
{
	free_token(data->ls_token);
	free_env(data->ls_env);
	ft_printf_err("exit\n");
	exit(OK);
}

int	str_is_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			if (i != 0 || !(arg[i] == '-' || arg[i] == '+'))
				return (0);
		}
		i++;
	}
	return (1);
}

static long long	check_valid_arg(char *arg)
{
	int					minus;
	unsigned long long	arg_ull;

	if (ft_strlen(arg) > 21)
	{
		ft_putendl_fd("Error: exit: numeric argument required", STDERR_FILENO);
		return (2);
	}
	if (!str_is_digit(arg))
	{
		ft_putendl_fd("Error: exit: numeric argument required", STDERR_FILENO);
		return (2);
	}
	minus = 1;
	arg_ull = ft_atoull(arg, &minus);
	if ((arg_ull > LLONG_MAX && minus == 1)
		|| (arg_ull > 9223372036854775808ULL && minus == -1))
	{
		ft_putendl_fd("Error: exit: numeric argument required", STDERR_FILENO);
		return (2);
	}
	return (arg_ull * minus);
}

static int	exit_arg(t_data *data, long long exit_code)
{
	int	exit_255;

	free_token(data->ls_token);
	free_env(data->ls_env);
	exit_255 = exit_code % 256;
	if (exit_255 < 0)
	{
		exit_255 += 256;
	}
	ft_printf_err("exit\n");
	exit(exit_255);
}

int	exec_exit(t_data *data, t_token *cmds)
{
	long long	exit_code;

	if (cmds->cmd[0] && cmds->cmd[1] && cmds->cmd[2])
	{
		ft_putendl_fd("Error exit: too many arguments", STDERR_FILENO);
		return (0);
	}
	if (!cmds->cmd[1])
	{
		exit_no_arg(data);
	}
	exit_code = check_valid_arg(cmds->cmd[1]);
	if (exit_code == -1)
	{
		return (0);
	}
	exit_arg(data, exit_code);
	return (1);
}
