#include "minishell.h"

void	free_token_env(t_data *data)
{
	free_token(data->ls_token);
	free_env(data->ls_env);
}

void	close_free_token_env(t_data *data, int fd0, int fd1)
{
	free_token_env(data);
	close_all(fd0, fd1);
}

char	*free_return_str(char *to_free, char *return_value)
{
	if (to_free)
		free(to_free);
	return (return_value);
}

int	free_array_return(char **array, int return_value)
{
	if (array)
		free_array(array);
	return (return_value);
}
