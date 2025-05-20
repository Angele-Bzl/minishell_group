// # include "minishell.h"

#include "../../../header/minishell.h"


static int	update_pwd(t_env **list_env, char *variable, int var_length)
{
	bool	pwd_exists;

	pwd_exists = false;
	while (*list_env)
	{
		if (ft_strncmp((*list_env)->line, variable, var_length))
		{
			free((*list_env)->line);
			(*list_env)->line = ft_strjoin(variable, getcwd(NULL, 0));
			if (!(*list_env)->line)
			{
				ft_putendl_fd("Error: update_pwd failed", STDERR_FILENO);
				return (0);
			}
			pwd_exists = true;
		}
		*list_env = (*list_env)->next;
	}
	if (pwd_exists == true)
		return (1);
	(*list_env)->line = ft_strjoin(variable, getcwd(NULL, 0));
	if (!(*list_env)->line)
	{
		ft_putendl_fd("Error: update_pwd failed", STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	exec_cd(char **cmd, t_env *list_env)
{
	if (cmd[2])
	{
		// ft_putendl_fd("Error: too many arguments", STDERR_FILENO);
		return (0);
	}
	/*mettre a jour env oldpwd si elle existe, sinon il faut la creer*/
	update_pwd(&list_env, "OLDPWD=", 7);
	if (chdir(cmd[1]) == -1)
	{
		perror("Error chdir:");
		return (0);
	}
	/*mettre a jour env pwd si la variable existe, sinon il faut la creer*/
	update_pwd(&list_env, "PWD=", 4);
	return (1);
}
static int  env_init_TEST(t_env **ls_env, char **env)//////////////////
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


static void print_env(t_env **ls_env)//////////
{
	while (*ls_env)
	{
		if (ft_strncmp((*ls_env)->line, "PWD=", 4) || ft_strncmp((*ls_env)->line, "OLDPWD=", 7))
		printf("%s\n", (*ls_env)->line);
		*ls_env = (*ls_env)->next;
	}
}
int main(int ac, char **av, char **env)
{
	t_env *ls_env;
	char *cmds[2] = {"cd", "../.."};

	ls_env = malloc(sizeof(t_env));
	env_init_TEST(&ls_env, env);
	printf("FIRST\n\n");
	print_env(&ls_env);
	printf("hello---------------\n");
	exec_cd(cmds, ls_env);
	printf("--------------------------------------------------\n\n");
	printf("SECOND\n\n");
	print_env(&ls_env);
}
