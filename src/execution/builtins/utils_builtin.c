# include "minishell.h"

int	cmd_is_builtin(char *path_cmd, char **env)
{ //pas sure du strncmp si une fonction s'appelle echooo par exemple
	if (!ft_strncmp(path_cmd, "echo", 4))
		return (1);
	if (!ft_strncmp(path_cmd, "cd", 2))
		return (1);
	if (!ft_strncmp(path_cmd, "pwd", 3))
		return (1);
	if (!ft_strncmp(path_cmd, "export", 6))
		return (1);
	if (!ft_strncmp(path_cmd, "unset", 5))
		return (1);
	if (!ft_strncmp(path_cmd, "env", 3))
		return (1);
	if (!ft_strncmp(path_cmd, "exit", 4))
		return (1);
	return (0);
}

int	exec_homemade_builtin(t_data *data, char **env)
{//pas sure du strncmp si une fonction s'appelle echooo par exemple
	if (!ft_strncmp(data->ls_token->cmd[0], "echo", 4))
		exec_echo(data->ls_token->cmd);
	if (!ft_strncmp(data->ls_token->cmd[0], "cd", 2))
	{
		if (!exec_cd(data->ls_token->cmd, data->ls_env))
			return (0);
	}
	if (!ft_strncmp(data->ls_token->cmd[0], "pwd", 3))
		exec_pwd(env);//
	if (!ft_strncmp(data->ls_token->cmd[0], "export", 6))
		//exec_export();//
	if (!ft_strncmp(data->ls_token->cmd[0], "unset", 5))
		//exec_unset();//
	if (!ft_strncmp(data->ls_token->cmd[0], "env", 3))
		//exec_env();//
	if (!ft_strncmp(data->ls_token->cmd[0], "exit", 4))
		//exec_exit();//
	data->ls_token = data->token_head;
	data->ls_env = data->env_head;
	return (1);
}
