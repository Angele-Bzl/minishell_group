#include "minishell.h"

int main(int ac, char **av, char **env)
{
	t_data      data;
	t_parsing   parsing;
	int			errcode;

	(void)ac;
	(void)av;
	errcode = OK;
	if (!env_init(env, &data))
		return (msg_return("Error: malloc failed\n", STDERR_FILENO, ERR));
	while (1)
	{
		struct_init(&data, &parsing);
		(&parsing)->prompt = readline("minishell> ");
		if ((&parsing)->prompt)
		{
			add_history((&parsing)->prompt);
			ft_parsing(&data, &parsing, &errcode);
			print_tokens(&data);
			if (errcode == OK)
			{
				if (execution(&data) == OK)
					free_token((&data)->ls_token);
			}
		}
	}
	return (OK);
}
