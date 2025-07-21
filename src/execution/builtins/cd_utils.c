#include "minishell.h"

t_env	*msg_return_t_env(char *msg, t_env *return_value)
{
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	return (return_value);
}

t_env	*create_var_pwd(char *variable, t_env *ls_env)
{
	char	*pwd;
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (msg_return_t_env("Error: update_pwd failed", NULL));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (msg_return_t_env(MALLOC, NULL));
	new_node->line = ft_strjoin(variable, pwd);
	free(pwd);
	if (!new_node->line)
	{
		free(new_node);
		return (msg_return_t_env("Error: update_pwd failed", NULL));
	}
	new_node->next = NULL;
	ft_lstadd_back((t_list **)&ls_env, (t_list *)new_node);
	return (new_node);
}
