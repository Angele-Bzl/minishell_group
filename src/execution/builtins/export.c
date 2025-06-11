#include "minishell.h"

// #include "../../../header/minishell.h"


/*
export with no argument
*/

int	exec_export(t_env *ls_env, char **cmds)
{
	int		i;
	t_env	*new;

	i = 1;
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
		ft_lstadd_back((t_list **)&ls_env, (t_list *)new);
		i++;
	}
	return (1);
}
// static int  env_init_TEST(t_env **ls_env, char **env)
// {
// 	unsigned int	i;
// 	t_env			*new_node;
// 	i = 0;
// 	while (env[i])
// 	{
// 		new_node = malloc(sizeof(t_env));
// 		if (!new_node)
// 			return (0);
// 		new_node->line = ft_strdup(env[i]);
// 		if (!new_node->line)
// 			return (0);
// 		new_node->next = NULL;
// 		ft_lstadd_back((t_list**)ls_env, (t_list*)new_node);
// 		new_node = new_node->next;
// 		i++;
// 	}
// 	return (1);
// }

// static void print_env(t_env *ls_env)
// {
// 	t_env	*current;
// 	current = ls_env;
// 	while (current)
// 	{
// 		if (!ft_strncmp((current)->line, "A=a", 3) || !ft_strncmp((current)->line, "Z=z", 3))
// 			printf("%s\n", (current)->line);
// 		current = (current)->next;
// 	}
// }

// int main(int ac, char **av, char **env)
// {
// 	t_env 	*ls_env;
// 	char *cmds[4] = {"export", "A=a", "Z=z", NULL};
// 	ls_env = NULL;
// 	env_init_TEST(&ls_env, env);
// 	printf("before export\n");
// 	print_env(ls_env);
// 	exec_export(ls_env, cmds);
// 	printf("after export\n");
// 	print_env(ls_env);
// }
