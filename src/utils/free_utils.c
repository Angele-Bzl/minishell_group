#include "minishell.h"

char	*free_array(char **array)
{
	int	i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

void	free_env(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env->next;
		free(env->line);
		free(env);
		env = tmp;
	}
}

void	free_token(t_token *token)
{
	t_token	*tmp;
	int		i;

	while (token)
	{
		tmp = token->next;
		if (token->cmd)
		{
			i = 0;
			while (token->cmd[i])
				free(token->cmd[i++]);
			free(token->cmd);
		}
		if (token->io_value[0])
			free(token->io_value[0]);
		if (token->io_value[1])
			free(token->io_value[1]);
		free(token);
		token = tmp;
	}
}
