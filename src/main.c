#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_data      data;
	t_parsing   parsing;

	if (!env_init(env, &data))
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return (ERR);
	}
	while (1)
	{
		struct_init(&data, &parsing);
		(&parsing)->prompt = readline("minishell> ");
		if ((&parsing)->prompt)
		{
			add_history((&parsing)->prompt);
			if (ft_parsing(&data, &parsing) != OK)
				break ;
			//(&data)->ls_token = (&data)->token_head;
			if (execution(&data) == OK)
				sleep(1); //free all (data)
		}
	}
	return (OK);
}
