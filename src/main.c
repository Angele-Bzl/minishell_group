#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>

sig_atomic_t	g_sigreceived;

static void	launch_set(int ac, char **av, char **env, t_data *data)
{
	if (!check_minishell_launch(ac, av))
		exit (EXIT_FAILURE);
	if (env_init(env, data) == ERR)
		exit(EXIT_FAILURE);
	g_sigreceived = 0;
	data->exit_status = OK;
}

static void	update_exit_status(t_data *data)
{
	data->exit_status = 130;
	g_sigreceived = 0;
}

int	main(int ac, char **av, char **env)
{
	t_data		data;
	t_parsing	parsing;

	launch_set(ac, av, env, &data);
	while (1)
	{
		if (struct_init(&data, &parsing) == ERR)
			return (EXIT_FAILURE);
		set_signals_on(PROMPT_MODE);
		parsing.prompt = readline("minishell> ");
		if (g_sigreceived == 1)
			update_exit_status(&data);
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
