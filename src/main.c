#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data      data;
	t_parsing   parsing;

	(void)ac;
	(void)av;
	if (!env_init(env, &data))
		msg_exit(MALLOC, NULL, EXIT_FAILURE);
	while (1)
	{
		if (struct_init(&data, &parsing) == ERR)
			return (EXIT_FAILURE);
		parsing.prompt = readline("minishell> ");
		if (parsing.prompt[0])
		{
			add_history(parsing.prompt);
			ft_parsing(&data, &parsing);
			// printf("EXEC\n");
			// print_tokens(&data); // attention ! peut faire segfault le code parfois
			if (parsing.errcode == OK)
			{
				execution(&data);
			}
		}
		// else
		// 	free_token(data.ls_token);
		if (parsing.prompt)
			free(parsing.prompt);
	}
	return (OK);
}
