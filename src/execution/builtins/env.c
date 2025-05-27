# include "minishell.h"


/*
env -i doit quand meme avoit quelques variables PWD SHLVL et _
SHLVL doit s'incrementer
*/
void exec_env(t_env *ls_env)
{
	t_env	*current;

	current = ls_env;
	while (current)
	{
		printf("%s\n", current->line);
		current = current->next;
	}
}