#include "minishell.h"

// static t_env	*msg_return_t_env(char *msg, t_env *return_value)
// {
// 	if (msg)
// 		ft_putendl_fd(msg, STDERR_FILENO);
// 	return (return_value);
// }

// static t_env	*create_var_pwd(char *variable, t_env *ls_env)
// {
// 	char	*pwd;
// 	t_env	*new_node;

// 	new_node = malloc(sizeof(t_env));
// 	if (!new_node)
// 		return (msg_return_t_env("Error: update_pwd failed", NULL));
// 	pwd = getcwd(NULL, 0);
// 	if (!pwd)
// 		return (msg_return_t_env(MALLOC, NULL));
// 	new_node->line = ft_strjoin(variable, pwd);
// 	free(pwd);
// 	if (!new_node->line)
// 	{
// 		free(new_node);
// 		return (msg_return_t_env("Error: update_pwd failed", NULL));
// 	}
// 	new_node->next = NULL;
// 	ft_lstadd_back((t_list **)&ls_env, (t_list *)new_node);
// 	return (new_node);
// }

static int	update_pwd(t_env *ls_env, int var_length)
{
	t_env	*current;
	char	*pwd;

	current = ls_env;
	while (current)
	{
		if (!ft_strncmp(current->line, "PWD=", var_length))
		{
			free(current->line);
			pwd = getcwd(NULL, 0);
			if (!pwd)
				return (msg_return(ERR_PWD, NULL, 0));
			current->line = ft_strjoin("PWD=", pwd);
			free(pwd);
			if (!current->line)
				return (msg_return(ERR_PWD, NULL, 0));
			break ;
		}
		current = current->next;
	}
	if (!current)
		return (0);
	return (1);
}

static char	*get_var_pwd(t_env *current, t_env *ls_env)
{
	char	*pwd;

	pwd = NULL;
	while (current)
	{
		if (!ft_strncmp(current->line, "PWD=", 4))
		{
			pwd = ft_strdup(current->line + 4);
			if (!pwd)
				return (msg_return_str(MALLOC, NULL, NULL));
			break ;
		}
		current = current->next;
	}
	current = ls_env;
	return (pwd);
}

static int	update_oldpwd(t_env *ls_env)
{
	t_env	*current;
	char	*pwd;

	current = ls_env;
	pwd = get_var_pwd(current, ls_env);
	if (!pwd)
		create_var_pwd("PWD=", ls_env);
	while (current)
	{
		if (!ft_strncmp(current->line, "OLDPWD=", 7))
		{
			free(current->line);
			current->line = ft_strjoin("OLDPWD=", pwd);
			if (pwd)
				free(pwd);
			if (!current->line)
				return (msg_return(ERR_OLDPWD, NULL, 0));
			return (1);
		}
		current = current->next;
	}
	current = create_var_pwd("OLDPWD=", ls_env);
	if (!current)
		return (0);
	return (1);
}

int	exec_cd(char **cmd, t_env *list_env, t_data *data)
{
	if (!cmd[1])
		return (OK);
	if (cmd[2])
	{
		data->exit_status = EXIT_PROMPT;
		return (msg_return(TOO_MANY_ARG, NULL, ERROR_PROMPT));
	}
	if (chdir(cmd[1]) == -1)
	{
		data->exit_status = EXIT_PROMPT;
		perror(cmd[1]);
		return (ERROR_PROMPT);
	}
	if (!update_oldpwd(list_env))
		return (ERROR_SYSTEM);
	if (!update_pwd(list_env, 4))
		return (ERROR_SYSTEM);
	return (OK);
}
