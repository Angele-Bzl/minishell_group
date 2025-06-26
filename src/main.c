#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;			// les deplacer dans un check, no args needed
	t_data      data;
	t_parsing   parsing;

	if (!env_init(env, &data))
		msg_exit(MALLOC, STDERR_FILENO, EXIT_FAILURE);
	// init_signals();
	while (1)
	{
		g_sig_state = 0;
		if (struct_init(&data, &parsing) != OK)
			return (EXIT_FAILURE);
		parsing.prompt = readline("minishell> ");
		if (parsing.prompt && parsing.prompt[0])
		{
			add_history(parsing.prompt);
			ft_parsing(&data, &parsing);
			// print_tokens(&data);
			if (parsing.errcode == OK)
			{
				execution(&data);
				free_token(data.ls_token);
			}
		}
	}
	return (OK);
}
