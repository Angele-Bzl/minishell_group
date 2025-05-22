# include "minishell.h"

void	print_prompt_tab(char **p_tab)
{
	int	i;

	i = 0;
	while (p_tab[i])
		printf("%s\n", p_tab[i++]);
}

void	print_env(t_env *env)
{
	int i;

	i = 1;
	printf("env tab :\n\n");
	while (env)
	{
		printf("%d) %s\n", i, env->line);
		env = env->next; 
		i++;
	}
}

void	print_tokens(t_data *data)
{
	int	i;

	i = 0;
	
}