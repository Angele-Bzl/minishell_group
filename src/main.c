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
        return(ALL_OK);
    struct_init(data, parsing, env);
        // return(free_all(data, parsing));
    print_env(data->ls_env);
    while (1)
    {
        parsing->prompt = readline("minishell > ");
        if (parsing->prompt)
		{
			add_history(parsing->prompt);
			if (!ft_parsing(data, parsing))
            {
                // free_all(data, parsing);
                // return (1);
            }
            // if (!execution(data))
            // {
                // free_data(data);
                // return (1);
            // }
		}
    }
    return (0);
}
