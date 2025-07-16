#include "minishell.h"

static t_env	*create_var_pwd(char *variable)
{
	char	*pwd;
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		ft_putendl_fd("Error: update_pwd failed", STDERR_FILENO);
		return (NULL);
	}
	pwd = getcwd(NULL, 0);
	new_node->line = ft_strjoin(variable, pwd);
	free(pwd);
	if (!new_node->line)
	{
		free(new_node);
		ft_putendl_fd("Error: update_pwd failed", STDERR_FILENO);
		return (NULL);
	}
	return (new_node);
}

static int	update_pwd(t_env *list_env, int var_length)
{
	t_env	*current;
	char	*pwd;

	current = list_env;
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
		current = create_var_pwd("PWD=");
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
				return (NULL);
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
		return (msg_return(ERR_OLDPWD, NULL, 0));
	while (current)
	{
		if (!ft_strncmp(current->line, "OLDPWD=", 7))
		{
			free(current->line);
			current->line = ft_strjoin("OLDPWD=", pwd);
			free(pwd);
			if (!current->line)
				return (msg_return(ERR_OLDPWD, NULL, 0));
			break ;
		}
		current = current->next;
	}
	if (!current)
		current = create_var_pwd("OLDPWD=");
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
		perror("Error chdir");
		return (ERROR_PROMPT);
	}
	if (!update_oldpwd(list_env))
		return (ERROR_SYSTEM);
	if (!update_pwd(list_env, 4))
		return (ERROR_SYSTEM);
	return (OK);
}
