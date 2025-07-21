#include "minishell.h"

void	exec_env_export(t_env *ls_env)
{
	t_env	*current;

	if (!ls_env)
	{
		ft_putstr_fd("Error: Environment list is NULL\n", STDERR_FILENO);
		return ;
	}
	current = ls_env;
	while (current)
	{
		printf("%s\n", current->line);
		current = current->next;
	}
}

void	exec_env(t_env *ls_env)
{
	t_env	*current;

	if (!ls_env)
	{
		ft_putstr_fd("Error: Environment list is NULL\n", STDERR_FILENO);
		return ;
	}
	current = ls_env;
	while (current)
	{
		if (ft_strchr(current->line, '='))
			printf("%s\n", current->line);
		current = current->next;
	}
}
