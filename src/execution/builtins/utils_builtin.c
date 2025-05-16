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

void	exec_homemade_builtin(t_data *data, char *path_cmd)
{
	(void)data;
	if (ft_strncmp(path_cmd, "echo", 4))
		//exec_echo();//
	if (ft_strncmp(path_cmd, "cd", 2))
		//exec_cd();//
	if (ft_strncmp(path_cmd, "pwd", 3))
		//exec_pwd();//
	if (ft_strncmp(path_cmd, "export", 6))
		//exec_export();//
	if (ft_strncmp(path_cmd, "unset", 5))
		//exec_unset();//
	if (ft_strncmp(path_cmd, "env", 3))
		//exec_env();//
	if (ft_strncmp(path_cmd, "exit", 4))
		//exec_exit();//
		return ;
}
