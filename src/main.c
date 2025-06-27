#include "minishell.h"

int main(int ac, char **av, char **env)
{
	t_data      data;
	t_parsing   parsing;

	ignore_ac_av(ac, av);
	if (!env_init(env, &data))
		msg_exit(MALLOC, STDERR_FILENO, EXIT_FAILURE);
	set_signals_exec();
	while (1)
	{
		if (struct_init(&data, &parsing) != OK)
			return (EXIT_FAILURE);
		set_signals_exec();
		parsing.prompt = readline("minishell> ");
		set_signals_exec();
		if (!parsing.prompt)
			process_empty_prompt(&parsing);
		if (parsing.prompt && parsing.prompt[0])
			parse_and_execute(&parsing, &data);
	}
	return (OK);
}
