#include "minishell.h"

void	exec_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putendl_fd("Error: pwd", STDERR_FILENO);
		// return (ERROR_SYSTEM);
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
	// return (OK);
	return ;
}
