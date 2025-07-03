#include "minishell.h"

// #include "../../../header/minishell.h"

static int	var_is_valid(char *cmd)
{
	if (!(ft_isalpha(cmd[0]) || cmd[0] == '_'))
	{
		printf("export: '%s': not a valid identifier\n", cmd);
		return (0);
	}
	return (1);
}

static int	var_new(t_env *ls_env, char *cmd)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (msg_return(MALLOC, NULL, 0));
	new->line = ft_strdup(cmd);
	if (!new->line)
		return (msg_return(MALLOC, NULL, 0));
	new->next = NULL;
	ft_lstadd_back((t_list **)&ls_env, (t_list *)new);
	return (1);
}

static int	var_already_exists(t_env *current, char *cmd)
{
	int i = 0;
	while (current)
	{
		i++;
		if (var_cmp(current->line, cmd))
		{
			return (1);
		}
		current = current->next;
	}
	return (0);
}

static int	var_update(t_env *current, char *cmd)
{
	while (current)
	{
		if (var_cmp(current->line, cmd))
		{
			free(current->line);
			current->line = ft_strdup(cmd);
			if (!current->line)
				return (msg_return(MALLOC, NULL, 0));
		}
		current = current->next;
	}
	return (1);
}



int	exec_export(t_env *ls_env, char **cmds)
{
	int		i;
	t_env	*current;

	current = ls_env;
	i = 1;
	if (!cmds[i])
	{
		exec_env_export(ls_env);
	}
	while (cmds[i])
	{
		if (var_is_valid(cmds[i]))
		{
			if (var_already_exists(current, cmds[i]))
			{
				if (!var_update(current, cmds[i]))
					return (ERROR_SYSTEM);
			}
			else if (!var_new(ls_env, cmds[i]))
				return (ERROR_SYSTEM);
		}
		i++;
	}
	return (OK);
}
