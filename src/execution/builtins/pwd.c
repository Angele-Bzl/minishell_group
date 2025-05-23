// # include "minishell.h"

#include "../../../header/minishell.h"

// void	exec_pwd(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (!ft_strncmp(env[i], "PWD=", 4))
// 			printf("%s\n", env[i] + 4);
// 		i++;
// 	}
// }


int	exec_pwd(char **env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putendl_fd("Error: pwd", STDERR_FILENO);
		return (0);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}

// int main(int ac, char **av, char **env)
// {
// 	exec_pwd(env);
// }
