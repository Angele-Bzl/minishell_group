#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data		data;
	t_parsing	parsing;

	if (!check_minishell_launch(ac, av))
		return (EXIT_FAILURE);
	// rl_event_hook = takes_a_value;
	if (env_init(env, &data) == ERR)
		msg_exit(MALLOC, NULL, EXIT_FAILURE);
	data.exit_status = 0;
	while (1)
	{
		if (struct_init(&data, &parsing) == ERR)
			return (EXIT_FAILURE);
		set_signals_on(PROMPT_MODE);
		parsing.prompt = readline("minishell> ");
		set_signals_on(EXEC_MODE);
		if (!parsing.prompt)
			process_empty_prompt(&parsing);
		if (parsing.prompt && parsing.prompt[0])
			parse_and_execute(&parsing, &data);
		if (parsing.prompt)
			free(parsing.prompt);
		if (data.ls_token)
			free_token(data.ls_token);
	}
	return (OK);
}
