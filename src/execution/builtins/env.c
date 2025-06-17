#include "minishell.h"

void exec_env(t_env *ls_env)
{
	t_env	*current;

	if (!ls_env)
    {
        printf("Error: Environment list is NULL\n");
        return;
    }
	current = ls_env;
	while (current)
	{
		printf("%s\n", current->line);
		current = current->next;
	}
}
