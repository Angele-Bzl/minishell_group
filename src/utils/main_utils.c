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

void	process_empty_prompt(t_parsing *parsing)
{
	write(1, "exit\n", 5);
	free_parsing(parsing);
	exit(0);
}

void	parse_and_execute(t_parsing *parsing, t_data *data)
{
	add_history(parsing->prompt);
	ft_parsing(data, parsing);
	print_tokens(data);
	if (parsing->errcode == OK)
		execution(data);
}
