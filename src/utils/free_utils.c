#include "minishell.h"

char	*free_array(char **array)
{
	int	i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		// printf("%s\n", array[i]);
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
	return (NULL);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->line);
		env->line = NULL;
		free(env);
		env = NULL;
		env = tmp;
	}
}

void	free_files(t_token *ls_token)
{
	t_file	*current;
	t_file	*next;

	current = ls_token->ls_infile;
	while (current)
	{
		next = current->next;
		if (current->value)
		{
			free(current->value);
			current->value = NULL;
		}
		free(current);
		current = next;
	}
	current = ls_token->ls_outfile;
	while (current)
	{
		next = current->next;
		if (current->value)
		{
			free(current->value);
			current->value = NULL;
		}
		free(current);
		current = next;
	}
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->cmd)
			free_array(token->cmd);
		if (token->ls_infile || token->ls_outfile)
			free_files(token);
		free(token);
		token = tmp;
	}
}
