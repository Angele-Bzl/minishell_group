# include "minishell.h"

int	cmd_is_builtin(char *path_cmd)
{
	if (ft_strncmp(path_cmd, "echo", 4))
		return (1);
	if (ft_strncmp(path_cmd, "cd", 2))
		return (1);
	if (ft_strncmp(path_cmd, "pwd", 3))
		return (1);
	if (ft_strncmp(path_cmd, "export", 6))
		return (1);
	if (ft_strncmp(path_cmd, "unset", 5))
		return (1);
	if (ft_strncmp(path_cmd, "env", 3))
		return (1);
	if (ft_strncmp(path_cmd, "exit", 4))
		return (1);
	return (0);
}

void	exec_homemade_builtin(t_data *data, int io_fd[2], char *path_cmd, int previous_output)
{
	(void)data;
	(void)io_fd;
	(void)previous_output;
	if (ft_strncmp(path_cmd, "echo", 4))
		/**/
	if (ft_strncmp(path_cmd, "cd", 2))
		/**/
	if (ft_strncmp(path_cmd, "pwd", 3))
		/**/
	if (ft_strncmp(path_cmd, "export", 6))
		/**/
	if (ft_strncmp(path_cmd, "unset", 5))
		/**/
	if (ft_strncmp(path_cmd, "env", 3))
		/**/
	if (ft_strncmp(path_cmd, "exit", 4))
		/**/
		return ;
}
