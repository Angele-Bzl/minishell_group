#include "minishell.h"

int	cmd_is_builtin(char *path_cmd)
{
	if (!path_cmd)
		return (0);
	if (!ft_strncmp(path_cmd, "echo\0", 5))
		return (1);
	if (!ft_strncmp(path_cmd, "cd\0", 3))
		return (1);
	if (!ft_strncmp(path_cmd, "pwd\0", 4))
		return (1);
	if (!ft_strncmp(path_cmd, "export\0", 7))
		return (1);
	if (!ft_strncmp(path_cmd, "unset\0", 6))
		return (1);
	if (!ft_strncmp(path_cmd, "env\0", 4))
		return (1);
	if (!ft_strncmp(path_cmd, "exit\0", 5))
		return (1);
	return (0);
}

int	exec_homemade_builtin(t_data *data, t_token *current, int *save_std_io)
{
	if (!ft_strncmp(current->cmd[0], "echo\0", 5))
		exec_echo(current->cmd);
	if (!ft_strncmp(current->cmd[0], "cd\0", 3))
		return (exec_cd(current->cmd, data->ls_env));
	if (!ft_strncmp(current->cmd[0], "pwd\0", 4))
		exec_pwd();
	if (!ft_strncmp(current->cmd[0], "export\0", 7))
		return (exec_export(data->ls_env, data->ls_token->cmd));
	if (!ft_strncmp(current->cmd[0], "unset\0", 6))
		exec_unset(&data->ls_env, data->ls_token->cmd);
	if (!ft_strncmp(current->cmd[0], "env\0", 4))
		exec_env(data->ls_env);
	if (!ft_strncmp(current->cmd[0], "exit\0", 5))
		exec_exit(data, current, save_std_io);
	return (OK);
}

int	var_cmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '=')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] != s2[i])
		return (0);
	return (1);
}
