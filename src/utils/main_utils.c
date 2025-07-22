#include "minishell.h"
#include <readline/history.h>

int	takes_a_value(void)
{
	return (1);
}

int	check_minishell_launch(int ac, char **av)
{
	(void)av;
	if (ac > 1)
	{
		ft_putstr_fd(TOO_MANY_ARG, STDERR_FILENO);
		return (0);
	}
	return (1);
}

void	process_empty_prompt(t_parsing *parsing, t_data *data)
{
	write(1, "exit\n", 5);
	free_parsing(parsing);
	free_token_env(data);
	exit(0);
}

int	tester_is_mean(t_data *data)
{
	int			i;
	int			minishell;
	t_token		*current;

	current = data->ls_token;
	minishell = 0;
	while (current)
	{
		i = 0;
		while (current->cmd && current->cmd[i])
		{
			if (!ft_strncmp(current->cmd[i], "./minishell\0", 12))
				minishell++;
			i++;
		}
		if (minishell >= 2)
			return (msg_return(PLEASE_DONT, NULL, 1));
		current = current->next;
	}
	return (0);
}

void	parse_and_execute(t_parsing *parsing, t_data *data)
{
	add_history(parsing->prompt);
	ft_parsing(data, parsing);
	if (tester_is_mean(data))
		return ;
	if (parsing->errcode == OK)
		execution(data);
}
