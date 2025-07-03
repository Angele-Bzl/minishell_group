#include "minishell.h"

void	free_parsing(t_parsing *parsing)
{
	if (parsing->prompt)
		free(parsing->prompt);
	if (parsing->prompt_tab)
		free_array(parsing->prompt_tab);
	parsing->prompt = NULL;
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
