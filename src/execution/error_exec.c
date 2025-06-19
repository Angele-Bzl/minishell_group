#include "minishell.h"

void	free_str_close_fds(char **array, char *str, int *fd)
{
	if (array)
		free_array(array);
	if (str)
		free(str);
	close(fd[0]);
	close(fd[1]);
}

int	free_str_close_fds_return(char **array, char *str, int *fd, int return_value)
{
	if (array)
		free_array(array);
	if (str)
		free(str);
	close(fd[0]);
	close(fd[1]);
	return (return_value);
}
void	free_token_and_env(t_data *data)
{
	free_token(data->ls_token);
	free_env(data->ls_env);
}

void	free_data_exit(t_data *data, int exit_value)
{
	free_token_and_env(data);
	exit(exit_value);
}
void	close_fds(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

int	perror_return(char *message, int return_value)
{
	if (message)
		perror(message);
	return (return_value);
}
