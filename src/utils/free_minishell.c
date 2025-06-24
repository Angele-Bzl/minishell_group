# include "minishell.h"

// void	close_all(t_data *data)
// {
// 	/*est-ce qu'on closerais pas dans l'exec avant l'appel de la fonction ?*/
// 	/*a moins d'avoir les fd en question en paramettre*/
// }

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
	//close_all(parsing->data);
	free_parsing(parsing);
	if (exitcode)
	{
	if (parsing->data->ls_env)
		free_env(parsing->data->ls_env);
	exit(exitcode);
	}
}
