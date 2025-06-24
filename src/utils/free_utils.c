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

void	free_infile(t_token *ls_token)
{
	t_infile	*current;
	t_infile	*next;

	current = ls_token->ls_infile;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		current = next;
	}
}

void	free_outfile(t_token *ls_token)
{
	t_outfile	*current;
	t_outfile	*next;

	current = ls_token->ls_outfile;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		current = next;
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
			{
				free(token->cmd[i]);
				i++;
			}
			free(token->cmd);
		}
		if (token->ls_infile)
			free_infile(token);
		if (token->ls_outfile)
			free_outfile(token);
		free(token);
		token = tmp;
	}
}
