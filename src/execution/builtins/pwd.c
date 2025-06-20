#include "minishell.h"

// #include "../../../header/minishell.h"

int	exec_pwd(void)
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
