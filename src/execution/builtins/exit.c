# include "minishell.h"
# include <limits.h>
// #include "../../../header/minishell.h"

static void	go_to_num(const char *str, int *i, int *minus)
{
	if (str[*i] == '+')
		*i = *i + 1;
	else if (str[*i] == '-')
	{
		*minus = -1;
		*i = *i + 1;
	}
}

unsigned long long	ft_atoull(const char *str, int *minus)
{
	unsigned long long	result;
	int					i;

	i = 0;
	result = 0;
	go_to_num(str, &i, minus);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
}

static int	exit_no_arg()
{
	/*free t_token*/
	/*free t_env*/
	exit(0);
}

static int check_valid_arg(char *arg)
{
	int	minus;
	unsigned long long	arg_ull;

	if (ft_strlen(arg) > 20)
	{
		ft_putendl_fd("Error: exit: numeric argument required", STDERR_FILENO);
		return (2);
	}
	if (!ft_isdigit())
	{
		ft_putendl_fd("Error: exit: numeric argument required", STDERR_FILENO);
		return (-1);
	}
	minus = 1;
	arg_ull = ft_atoull(arg, &minus);
	if ((arg_ull > LLONG_MAX && minus == 1) ||(arg_ull > LLONG_MAX + 1 && minus == -1))
	{
		ft_putendl_fd("Error: exit: numeric argument required", STDERR_FILENO);
		return (2);
	}
	return (arg_ull * minus);
}

int	exec_exit(t_token *cmds, t_env *ls_env)
{
	int	exit_code;

	if (cmds->cmd[0] && cmds->cmd[1] && cmds->cmd[2])
	{
		ft_putendl_fd("Error exit: too many arguments", STDERR_FILENO);
		return (0);
	}

	if (!cmds->cmd[1])
	{
		exit_no_arg();
	}
	else
	{
		exit_code = check_valid_arg(cmds->cmd[1]);
		if (exit_code == -1)
		{
			return (0);
		}
		exit_arg();
	}
	return (1);
}