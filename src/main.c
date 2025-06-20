#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_data      data;
	t_parsing   parsing;

	if (!env_init(env, &data))
		msg_exit("Error: malloc failed\n", STDERR_FILENO, ERR);
	while (1)
	{
		struct_init(&data, &parsing);
		(&parsing)->prompt = readline("minishell> ");
		if ((&parsing)->prompt)
		{
			add_history((&parsing)->prompt);
			ft_parsing(&data, &parsing);
			// print_tokens(&data);
<<<<<<< HEAD
			if (errcode == OK)
			{
				execution(&data);
				free_token((&data)->ls_token);
			}
=======
			if ((&parsing)->errcode == ALL_OK)
				if (execution(&data) == OK)
					sleep(1); //free all (data)
>>>>>>> 1a75730cfddd95da2b32b1fdb50098e795790121
		}
	}
	return (OK);
}
