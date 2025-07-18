#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>

sig_atomic_t	g_sigreceived;

int	main(int ac, char **av, char **env)
{
	t_data		data;
	t_parsing	parsing;

	if (!check_minishell_launch(ac, av))
		return (EXIT_FAILURE);
	if (env_init(env, &data) == ERR)
		msg_exit(MALLOC, NULL, EXIT_FAILURE);
	g_sigreceived = 0;
	data.exit_status = OK;
	while (1)
	{
		if (struct_init(&data, &parsing) == ERR)
			return (EXIT_FAILURE);
		set_signals_on(PROMPT_MODE);
		parsing.prompt = readline("minishell> ");
		if (g_sigreceived == 1)
		{
			data.exit_status = 130;
			g_sigreceived = 0;
		}
		set_signals_on(EXEC_MODE);
		if (!parsing.prompt)
			process_empty_prompt(&parsing, &data);
		if (parsing.prompt && parsing.prompt[0])
			parse_and_execute(&parsing, &data);
		if (parsing.prompt)
			free(parsing.prompt);
		if (data.ls_token)
			free_token(data.ls_token);
	}
	return (OK);
}
