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
	return (result);
}

static int	exit_no_arg()
{
	/*free t_token*/
	/*free t_env*/
	exit(0);
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

static long long check_valid_arg(char *arg)
{
	int	minus;
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
	if ((arg_ull > LLONG_MAX && minus == 1) || (arg_ull > LLONG_MAX + 1 && minus == -1))
	{
		ft_putendl_fd("Error: exit: numeric argument required", STDERR_FILENO);
		return (2);
	}
	printf("argull = %llu\n", arg_ull);
	return (arg_ull * minus);
}

static long long	exit_arg(long long exit_code)
{
	int exit_255;

	/*free all*/
	printf("exit arg : exit code : %lld\n" , exit_code);
	exit_255 = exit_code % 256;
	if (exit_255 < 0)
	{
		exit_255 += 256;
	}
	printf("exit arg : exit 255 : %d\n", exit_255);
	exit(exit_255);
}
int	exec_exit(t_token *cmds, t_env *ls_env)
{
	long long	exit_code;

	if (cmds->cmd[0] && cmds->cmd[1] && cmds->cmd[2])
	{
		ft_putendl_fd("Error exit: too many arguments", STDERR_FILENO);
		return (0);
	}
	if (!cmds->cmd[1])
	{
		exit_no_arg();//
	}
	exit_code = check_valid_arg(cmds->cmd[1]);
	printf("exec exit : exit code = %lld\n", exit_code);
	if (exit_code == -1)
	{
		return (0);
	}
	exit_arg(exit_code);
	return (1);
}


// static int  env_init_TEST(t_env **ls_env, char **env)
// {
// 	unsigned int	i;
// 	t_env			*new_node;
// 	i = 0;
// 	while (env[i])
// 	{
// 		new_node = malloc(sizeof(t_env));
// 		if (!new_node)
// 			return (0);
// 		new_node->line = ft_strdup(env[i]);
// 		if (!new_node->line)
// 			return (0);
// 		new_node->next = NULL;
// 		ft_lstadd_back((t_list**)ls_env, (t_list*)new_node);
// 		new_node = new_node->next;
// 		i++;
// 	}
// 	return (1);
// }

// int main(int ac, char **av, char **env)
// {
// 	t_env 	*ls_env;
// 	t_token	*token;
// 	char *cmds[3] = {"exit", "9223372036854775808", NULL};
// 	ls_env = NULL;
// 	env_init_TEST(&ls_env, env);
// 	token = malloc(sizeof(t_token));
// 	token->cmd = cmds;
// 	token->next = NULL;
// 	exec_exit(token, ls_env);
// }