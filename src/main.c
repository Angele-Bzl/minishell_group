# include "minishell.h"

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_data      *data;
    t_parsing   *parsing;

    data = malloc(sizeof(t_data));
    parsing = malloc(sizeof(t_parsing));
    if (!data || !parsing)
	{
		if (data)
			free(data);
		if (parsing)
			free(parsing);
		ft_putstr_fd("Error: malloc failed\n", 2);
		return (2);
	}
	// if (!struct_init(data, parsing, env))
	// {
    //     // return(free_all(data, parsing));
	// }
        // return(ALL_OK);
    while (1)
    {
        if (!struct_init(data, parsing, env))
            print_and_free(NULL, data, parsing);
        parsing->prompt = readline("minishell > ");
        if (parsing->prompt)
		{
			add_history(parsing->prompt);
			ft_parsing(data, parsing);
            if (!execution(data))
            {
                // free_all(data);
                return (1);
            }
		}
    }
    print_and_free(NULL, data, parsing);
    free(data);
    free(parsing);
    return (0);
}
