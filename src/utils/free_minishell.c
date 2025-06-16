# include "minishell.h"

// void	close_all(t_data *data)
// {
// 	/*est-ce qu'on closerais pas dans l'exec avant l'appel de la fonction ?*/
// 	/*a moins d'avoir les fd en question en paramettre*/
// }

void	free_data(t_data *data)
{
	if (data->ls_token)
	free_token(data->ls_token);
	if (data->ls_env)
	free_env(data->ls_env);
	free(data);
}

void	free_all(t_parsing *parsing)
{
	if (parsing->prompt)
	free(parsing->prompt);
	if (parsing->prompt_tab)
	free_array(parsing->prompt_tab);
	if (parsing->data)
	free_data(parsing->data);
	free(parsing);
}

void	close_free_maybe_exit(t_parsing *parsing, char *errormsg, void *argument, int exitcode)
{
	if (errormsg && !argument)
		ft_printf_err(errormsg);
	else if (errormsg && argument)
		ft_printf_err(errormsg, argument);
	//close_all(parsing->data);
	free_all(parsing);
	if (exitcode)
		exit(exitcode);
}
