// # include "minishell.h"

#include "../../../header/minishell.h"

void	exec_unset(t_env *ls_env, char **cmds)
{
	int		i;
	t_env	*current;
	t_env	*previous;
	bool	unset_done;

	current = ls_env;
	previous = NULL;
	while (current)
	{
		i = 1;
		unset_done = false;
		while (cmds[i])
		{
			if (!ft_strncmp(current->line, cmds[i], ft_strlen(cmds[i])))
			{//nonnnn parce que si je veux suppr $A je vais aussi suppr $Allo
				//strjoin le '=' ?
				//update ls_env si c'est le premier node qui se fait unset
				previous->next = current->next;
				free(current);
				unset_done = true;
				break ;
			}
			i++;
		}
		if (unset_done)
			current = previous->next;
		else
		{
			previous = current;
			current = current->next;
		}
	}
}


static int  env_init_TEST(t_env **ls_env, char **env)
{
	unsigned int	i;
	t_env			*new_node;
	i = 0;
	while (env[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (0);
		new_node->line = ft_strdup(env[i]);
		if (!new_node->line)
			return (0);
		new_node->next = NULL;
		ft_lstadd_back((t_list**)ls_env, (t_list*)new_node);
		new_node = new_node->next;
		i++;
	}
	return (1);
}

static void print_env(t_env *ls_env)
{
	t_env	*current;
	current = ls_env;
	while (current)
	{
		if (!ft_strncmp((current)->line, "A=a", 3) || !ft_strncmp((current)->line, "Z=z", 3))
			printf("%s\n", (current)->line);
		current = (current)->next;
	}
}




int	exec_export(t_env *ls_env, char **cmds)
{
	int		i;
	t_env	*new;

	i = 0;
	while (cmds[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
		{
			ft_putendl_fd("Error exec_export: malloc failed", STDERR_FILENO);
			return (0);
		}
		new->line = cmds[i];
		new->next = NULL;
		ft_lstadd_back((t_list**)&ls_env, (t_list*)new);
		i++;
	}
	return (1);
}
int main(int ac, char **av, char **env)
{
	t_env 	*ls_env;
	char 	*cmds[4] = {"export", "A=a", "Z=z", NULL};
	char	*cmds_unset[3]={"unset", "A", NULL};
	ls_env = NULL;
	env_init_TEST(&ls_env, env);
	printf("before export\n");
	print_env(ls_env);
	exec_export(ls_env, cmds);
	printf("after export\n");
	print_env(ls_env);
	exec_unset(ls_env, cmds_unset);
}
