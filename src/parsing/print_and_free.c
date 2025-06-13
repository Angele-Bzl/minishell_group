# include "minishell.h"

void	close_all(t_data *data)
{
	/*est-ce qu'on closerais pas dans l'exec avant l'appel de la fonction ?*/
	/*a moins d'avoir les fd en question en paramettre*/
}

void	free_parsing(t_parsing *parsing)
{

}

void	free_data(t_data *data)
{

}

void	free_all(t_parsing *parsing)
{
	free_parsing(parsing);
	free_data(parsing->data);
}

void	close_free_maybe_exit(t_parsing *parsing, char *errormsg, void *argument, int exitcode)
{
	if (errormsg && !argument)
		ft_printf_err(errormsg);
	else if (errormsg && argument)
		ft_printf_err(errormsg, argument);
	close_all(parsing->data);
	free_all(parsing);
	if (exitcode)
		exit(exitcode);
}
