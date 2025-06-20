#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_data      data;
	t_parsing   parsing;
	int			errcode;

	errcode = OK;
	if (!env_init(env, &data))
		msg_exit("Error: malloc failed\n", STDERR_FILENO, ERR);
	while (1)
	{
		struct_init(&data, &parsing);
		(&parsing)->prompt = readline("minishell> ");
		if ((&parsing)->prompt)
		{
			add_history((&parsing)->prompt);
			ft_parsing(&data, &parsing, &errcode);
			// print_tokens(&data);
			if (errcode == OK)
			{
				execution(&data);
				free_token((&data)->ls_token);
			}
		}
	}
	return (OK);
}
