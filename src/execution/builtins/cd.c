#include "minishell.h"

// #include "../../../header/minishell.h"

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
			if (current->line)
				free(current->line);
			pwd = getcwd(NULL, 0);
			if (!pwd)
			{
				ft_putendl_fd("Error: update_pwd failed", STDERR_FILENO);
				return (0);
			}
			current->line = ft_strjoin("PWD=", pwd);
			free(pwd);
			if (!current->line)
			{
				ft_putendl_fd("Error: update_pwd failed", STDERR_FILENO);
				return (0);
			}
			break ;
		}
		current = current->next;
	}
	if (!current)
	{
		current = create_var_pwd("PWD=");
		if (!current)
			return (0);
	}
	return (1);
}

static int	update_oldpwd(t_env *ls_env)
{
	t_env	*current;
	char	*pwd;

	current = ls_env;
	pwd = NULL;
	while (current)
	{
		if (!ft_strncmp(current->line, "PWD=", 4))
		{
			pwd = ft_strdup(current->line + 4);
			if (!pwd)
			{
				ft_putendl_fd("Error: update_oldpwd failed", STDERR_FILENO);
				return (0);
			}
			break ;
		}
		current = current->next;
	}
	current = ls_env;
	while (current)
	{
		if (!ft_strncmp(current->line, "OLDPWD=", 7))
		{
			free(current->line);
			current->line = ft_strjoin("OLDPWD=", pwd);
			free(pwd);
			if (!current->line)
			{
				ft_putendl_fd("Error: update_oldpwd failed", STDERR_FILENO);
				return (0);
			}
			break ;
		}
		current = current->next;
	}
	if (!current)
	{
		current = create_var_pwd("OLDPWD=");
		if (!current)
			return (0);
	}
	return (1);
}

int	exec_cd(char **cmd, t_env *list_env)
{
	printf("exec_cd\n");
	// printf("env ls = %s\n", list_env->line);
	if (cmd[2])
	{
		ft_putendl_fd("Error: too many arguments", STDERR_FILENO);
		return (0);
	}
	if (!update_oldpwd(list_env))
		return (0);
	if (chdir(cmd[1]) == -1)
	{
		perror("Error chdir");
		return (0);
	}
	if (!update_pwd(list_env, 4))
		return (0);
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
// 		if (!ft_strncmp((current)->line, "PWD=", 4) || !ft_strncmp((current)->line, "OLDPWD=", 7))
// 		printf("%s\n", (current)->line);
// 		current = (current)->next;
// 	}
// }

// int main(int ac, char **av, char **env)
// {
// 	t_env 	*ls_env;
// 	char 	*cmds[3] = {"cd", "../..", NULL};
// 	ls_env = NULL;
// 	env_init_TEST(&ls_env, env);
// 	printf("FIRST\n\n");
// 	print_env(ls_env);
// 	printf("cwd = %s\n", getcwd(NULL, 0));
// 	printf("---------------\n");
// 	exec_cd(cmds, ls_env);
// 	printf("---------------\n");
// 	printf("SECOND\n\n");
// 	print_env(ls_env);
// 	printf("cwd = %s\n", getcwd(NULL, 0));
// }
