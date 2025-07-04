#include "minishell.h"

int	takes_a_value(void)
{
	return (1);
}

void	ignore_ac_av(int ac, char **av)
{
	(void)ac;
	(void)av;
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
	// print_tokens(data);
	if (parsing->errcode == OK)
		execution(data);
}
