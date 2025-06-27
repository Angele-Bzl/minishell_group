# include "minishell.h"

void	free_data(t_data *data)									// ne pas free env maintenant
{
	if (data->ls_token)
		free_token(data->ls_token);
}

void	free_parsing(t_parsing *parsing)
{
	if (parsing->prompt)
		free(parsing->prompt);
	if (parsing->prompt_tab)
		free_array(parsing->prompt_tab);
	if (parsing->data)
		free_data(parsing->data);
}

void	close_free_maybe_exit(t_parsing *parsing, int exitcode)
{
	free_parsing(parsing);
	if (exitcode)
	{
		if (parsing->data->ls_env)
			free_env(parsing->data->ls_env);
		exit(exitcode);
	}
}
