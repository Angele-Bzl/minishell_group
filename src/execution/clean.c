#include "minishell.h"

void	free_token_env(t_data *data)
{
	free_token(data->ls_token);
	free_env(data->ls_env);
}

void	close_all(int fd0, int fd1)
{
	if (!(fd0 == STDIN_FILENO || fd0 == STDOUT_FILENO || fd0 == -1))
		close(fd0);
	if (!(fd1 == STDIN_FILENO || fd1 == STDOUT_FILENO || fd1 == -1))
		close(fd1);
}

void	close_free_token_env(t_data *data, int fd0, int fd1)
{
	free_token_env(data);
	close_all(fd0, fd1);
}

void	close_free_token_env_pids(t_data *data, int fd0, int fd1, pid_t *pids)
{
	free_token_env(data);
	close_all(fd0, fd1);
	free(pids);
}

void	close_free_array_str(int fd0, int fd1, char **env, char *path)
{
	close_all(fd0, fd1);
	if (env)
		free_array(env);
	if (path)
		free(path);
}
