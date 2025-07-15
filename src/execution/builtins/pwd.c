#include "minishell.h"

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
