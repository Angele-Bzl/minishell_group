# include "minishell.h"

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
		if (token->io_redir[0])
			free(token->io_redir[0]);
		if (token->io_redir[1])
			free(token->io_redir[1]);
		free(token);
		token = tmp;
	}
}

void	free_data(t_data *data)
{
	if (!data)
		return;
	if (data->ls_env)
		free_env(data->env_head);
	if (data->ls_token)
		free_token(data->token_head);
	data->env_head = NULL;
	data->ls_env = NULL;
	data->token_head = NULL;
	data->ls_token = NULL;
}

void	free_parsing(t_parsing *parsing)
{
	if (!parsing)
		return;
	if (parsing->prompt)
		free(parsing->prompt);
	if (parsing->prompt_tab)
		free_tab(parsing->prompt_tab);
	if (parsing->data)
		free(parsing->data);
	free(parsing);
}

void	free_all(t_data *data, t_parsing *parsing)
{
	free_data(data);
	free_parsing(parsing);
	exit(1);
}
