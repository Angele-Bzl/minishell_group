// # include "minishell.h"

#include "../../../header/minishell.h"

int	exec_cd(char **cmd, char **env)
{
	if (!env || !env[0])
	{
		// ft_putendl_fd("Error: no environment", STDERR_FILENO);
		return (0);
	}
	if (cmd[2])
	{
		// ft_putendl_fd("Error: too many arguments", STDERR_FILENO);
		return (0);
	}

	if (chdir(cmd[1]) == -1)
	{
		perror("Error chdir:");
		return (0);
	}
	/*mettre a jour env pwd si la variable existe, sinon il faut la creer*/
	/*mettre a jour env oldpwd si elle existe, sinon il faut la creer*/
	return (1);
}

void print_pwd(char **env)
{
	int i;

	i = 0;
	while (strncmp(env[i], "PWD=", 4))
		i++;
	printf("%s\n", env[i]);
}

int main(int ac, char **av, char **env)
{
	char	cwd[10000];

	print_pwd(env);

	if (chdir("/home") == -1)
		perror("Error chdir:");
	else
		printf("success :)\n");

	if(getcwd(cwd, sizeof(cwd)) != NULL)
		printf("cwd : %s\n", cwd);
	else
		perror("Error: getcwd");
	print_pwd(env);
}