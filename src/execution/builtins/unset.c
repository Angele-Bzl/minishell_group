#include "minishell.h"

static void	update_ls_env_head(t_env **ls_env, t_env **current)
{
	*ls_env = (*current)->next;
	free((*current)->line);
	free(*current);
	*current = *ls_env;
}

static void	update_pointers(t_env *previous, t_env **ls_env, t_env *current)
{
	if (previous == NULL)
		update_ls_env_head(ls_env, &current);
	else
	{
		previous->next = current->next;
		free(current->line);
		free(current);
	}
}

void	exec_unset(t_env **ls_env, char **cmds)
{
	int		i;
	t_env	*current;
	t_env	*previous;

	current = *ls_env;
	previous = NULL;
	while (current)
	{
		i = 1;
		while (cmds[i])
		{
			if (!ft_strncmp(current->line, cmds[i], ft_strlen(cmds[i])))
			{
				update_pointers(previous, ls_env, current);
				return ;
			}
			i++;
		}
		previous = current;
		current = current->next;
	}
}
